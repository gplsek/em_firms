<?php
// $Id$

/**
 * @file
 * Encryption functionality for the Field encrypt module.
 */

function field_encrypt_do_encrypt($field_info, $phrase) {
  $fields = array('field_name', 'entity_type', 'bundle', 'deleted', 'entity_id', 'revision_id', 'language', 'delta', 'value');
  $loop_fields = array('entity_type', 'bundle', 'deleted', 'entity_id', 'revision_id', 'language', 'delta');

  $inserts = array();

  $field_name = $field_info['field_name'];
  $table = 'field_data_' . $field_name;

  // Get all the current entries
  $results = db_select($table, 't')->fields('t')->execute();

  // For each result build the insert data for field_encrypt
  foreach ($results as $result) {
    $insert = array(
      'field_name' => $field_name,
    );
    foreach ($loop_fields as $field) {
      $insert[$field] = $result->$field;
      unset($result->$field);
    }
    if (isset($field_info['settings']['field_encrypt'])) {
      $insert['value'] = field_encrypt_encrypt(serialize($result), $field_info['settings']['field_encrypt']['phrase']); // encrypt here
    }
    $inserts[] = $insert;
  }

  // Do we have anything to insert?
  if (!empty($inserts)) {
    // Build the multiple insert query and do it.
    $query = db_insert('field_encrypt')->fields($fields);
    foreach ($inserts as $insert) {
      $query->values($insert);
    }
    $query->execute();

    // remove the rows from the original table
    db_delete($table)->execute();
  }
  drupal_set_message(t('%field_name is now being encrypted', array('%field_name' => $field_name)));
}

//-------------------------------------------------------

function field_encrypt_un_encrypt($field_info, $phrase) {
  $base_fields = array('entity_type', 'bundle', 'deleted', 'entity_id', 'revision_id', 'language', 'delta');

  $inserts = array();

  $field_name = $field_info['field_name'];
  $results = db_select('field_encrypt', 'fe')
  ->fields('fe')
  ->condition('fe.field_name', $field_name)
  ->execute();

  $index = strlen($field_name) + 1;
  foreach ($results as $result) {
    $fields = $base_fields;
    $insert = array();
    foreach ($fields as $field) {
      $insert[$field] = $result->$field;
    }

    $value = field_encrypt_decrypt($result->value, $field_info['settings']['field_encrypt']['phrase']);
    foreach ((array) unserialize($value) as $key => $val) {
      $insert[$key] = $val;
      $fields[] = $key;
    }
    $inserts[] = $insert;
  }

  if (!empty($inserts)) {
    // Build the multiple insert query and do it.
    $query = db_insert("field_data_$field_name")->fields($fields);
    foreach ($inserts as $insert) {
      $query->values($insert);
    }
    $query->execute();

    // remove the rows from the original table
    db_delete('field_encrypt')->condition('field_name', $field_name)->execute();
  }
  drupal_set_message(t('%field_name is no longer being encrypted', array('%field_name' => $field_name)));
}

//-------------------------------------------------------

function field_encrypt_re_encrypt($field_info, $new_phrase) {
  $fields = array('field_name', 'entity_type', 'entity_id', 'revision_id', 'language', 'delta');

  // Fetch all the relevant rows
  $field_name = $field_info['field_name'];
  $results = db_select('field_encrypt', 'fe')
  ->fields('fe')
  ->condition('fe.field_name', $field_name)
  ->execute();

  $updates = array();
  foreach ($results as $result) {
    $update = array();
    foreach ($fields as $field) {
      $update[$field] = $result->$field;
    }
    $value = field_encrypt_decrypt($result->value, $field_info['settings']['field_encrypt']['phrase']);
    $update['value'] =  field_encrypt_encrypt($value, $new_phrase);

    $updates[] = $update;
  }

  // For each update, update it.
  foreach ($updates as $update) {
    $value = $update['value'];
    unset($update['value']);

    $query = db_update('field_encrypt')
    ->fields(array('value' => $value));
    foreach ($update as $key => $val) {
      $query->condition($key, $val);
    }
    $query->execute();
  }
  drupal_set_message(t('Encryption phrase changed for %field_name.', array('%field_name' => $field_name)));
}

//-------------------------------------------------------

/**
 * Implements hook_field_storage_pre_insert().
 */
function _field_encrypt_field_storage_pre_insert($entity_type, $entity, &$skip_fields) {
  _field_encrypt_field_storage_pre_update($entity_type, $entity, $skip_fields);
}

/**
 * Implements hook_field_storage_pre_update().
 */
function _field_encrypt_field_storage_pre_update($entity_type, $entity, &$skip_fields) {
  static $field_info = NULL;
  if ($field_info===NULL) {
    $field_info = field_info_field_by_ids();
  }

  list($id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);
  if (is_null($vid)) {
    $vid = $id;
  }
  $default_options = array(
    'default' => FALSE,
    'deleted' => FALSE,
    'language' => NULL,
  );
  $instances = _field_invoke_get_instances($entity_type, $bundle, $default_options);

  $merge_base = array(
    'entity_type' => $entity_type,
    'entity_id' => $id,
    'revision_id' => $vid,
  );

  foreach ($instances as $instance) {
    // Get the field data
    $field_id = $instance['field_id'];
    $field = $field_info[$field_id];

    // Are we encrypting this field?
    if (!isset($field['settings']['field_encrypt']['encrypt'])) {
      // encryption setting does not exist, skip it
      continue;
    }
    if (!$field['settings']['field_encrypt']['encrypt']) {
      // encryption setting is set to FALSE, skip it
      continue;
    }
    $field_name = $instance['field_name'];

    // We're bypassing usual storage, mark field for skipping
    $skip_fields[$field_id] = $field;

    // If there's nothing in the field, go no further
    if (empty($entity->$field_name)) {
      continue;
    }

    $merge_keys = array_merge($merge_base, array('field_name' => $field_name));

    // Now we need to insert the data, we can't do multiple
    // merges so we have to do each language/delta separately.
    foreach ($entity->$field_name as $language => $items) {
      $merge_keys['language'] = $language;
      foreach ($items as $delta => $item) {
        $merge_keys['delta'] = $delta;
        $value = array();
        foreach ($item as $key => $val) {
          $value["{$field_name}_$key"] = $val;
        }
        db_merge('field_encrypt')
        ->key($merge_keys)
        ->fields(array('value' => field_encrypt_encrypt(serialize($value), $field['settings']['field_encrypt']['phrase']))) // encrypt here
        ->execute();
      }
    }
  }
}

/**
 * Implements hook_field_storage_pre_load().
 */
function _field_encrypt_field_storage_pre_load($entity_type, $queried_entities, $age, &$skip_fields, $options) {
  static $field_info = NULL;
  if ($field_info===NULL) {
    $field_info = field_info_field_by_ids();
  }

  foreach ($queried_entities as $entity) {
    list($id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);
    if (is_null($vid)) {
      $vid = $id;
    }
    $default_options = array(
    'default' => FALSE,
    'deleted' => FALSE,
    'language' => NULL,
    );
    $instances = _field_invoke_get_instances($entity_type, $bundle, $default_options);

    foreach ($instances as $instance) {
      // Get the field data
      $field_id = $instance['field_id'];
      $field = $field_info[$field_id];

      // Are we encrypting this field?
      if (!isset($field['settings']['field_encrypt']['encrypt'])) {
        continue;
      }
      if (!$field['settings']['field_encrypt']['encrypt']) {
        continue;
      }
      $field_name = $instance['field_name'];

      // We're bypassing usual storage, mark field for skipping
      $skip_fields[$field_id] = $field;

      // Now we need to fetch the encrypted data
      $results = db_select('field_encrypt', 'fe', array('fetch' => PDO::FETCH_ASSOC))
      ->fields('fe', array('language', 'delta', 'value'))
      ->condition('fe.field_name', $field_name)
      ->condition('fe.entity_type', $entity_type)
      ->condition('fe.entity_id', $id)
      ->condition('fe.revision_id', $vid)
      ->orderBy('fe.language', 'ASC')
      ->orderBy('fe.delta', 'ASC')
      ->execute();
      $field_data = array();
      $index = strlen($field_name) + 1;
      foreach ($results as $result) {
        extract($result); // decrypt here
        $value = field_encrypt_decrypt($value, $field['settings']['field_encrypt']['phrase']);

        $item = array();
        foreach ((array) unserialize($value) as $key => $val) {
          $item[substr($key, $index)] = $val;
        }
        $field_data[$language][$delta] = $item;
      }
      $entity->$field_name = $field_data;
    }
  }
}

/**
 * Encrypt raw message
 */
function field_encrypt_encrypt($raw, $key) {
  $salt_hash = _field_encrypt_salt_hash($key);
  $encrypted = mcrypt_encrypt(MCRYPT_3DES, $salt_hash, $raw, 'ecb');
  return base64_encode($encrypted);
}

/**
 * Decrypt encrypted message
 */
function field_encrypt_decrypt($encrypted64, $key) {
  $salt_hash = _field_encrypt_salt_hash($key);
  $encrypted = base64_decode($encrypted64);
  $decrypted = mcrypt_decrypt(MCRYPT_3DES, $salt_hash, $encrypted, 'ecb');
  return rtrim($decrypted, "\0");
}

/**
 * Make salted and hashed key.
 */
function _field_encrypt_salt_hash($key) {
  static $hashes = array();
  if (!isset($hashes[$key])) {
    $length = strlen($key)<=24 ? strlen($key) : 24;
    $hashes[$key] = substr(hash('sha512', $key . drupal_get_hash_salt()), 0, $length);
  }
  return $hashes[$key];
}
