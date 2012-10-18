<?php
// $Id$

/**
 * @file
 * Administrative interface for the Field encrypt module.
 */

/**
 * Alter the field settings form.
 */
function _field_encrypt_field_settings_form_alter(&$form, &$form_state, $form_id) {


  // Obtain the field name from form (should really be $form_state,
  // but the Date field doesn't comply).
  $field_name = $form['#field']['field_name'];

  // Try to obtain information about this field.
  $field_info = field_info_field($field_name);
  $field_type_info = field_info_field_types($field_info['type']);

  // If this field type cannot be encrypted, exit here
  #  if ($field_type_info['property_type']!='text') {
  #    return;
  #  }

  $fld_settings =& $field_info['settings'];

  $can_change = variable_get('FIELD_ENCRYPT_CHANGEABLE', TRUE);
  if(!$can_change) {
    if(!empty($fld_settings['field_encrypt']['phrase'])) {
      drupal_set_message('This field is encrypted but the encyrption information cannot be edited. See site admin to change these settings.');
    }
   return;
  }
  $form_state['field_encrypt'] = array(
    'field_name' => $field_name,
    'field_info' => $field_info,
    'field_type_info' => $field_type_info,
    'encrypt' => isset($fld_settings['field_encrypt']) ? $fld_settings['field_encrypt']['encrypt'] : FALSE,
    'phrase' => isset($fld_settings['field_encrypt']) ? $fld_settings['field_encrypt']['phrase'] : ''
  );

  $settings =& $form['field']['settings'];

  $settings['field_encrypt'] = array(
    '#type' => 'fieldset',
    '#title' => t('Encrypt this field'),
    '#description' => t('Set up the parameters for encrypting this text field.'),
    '#element_validate' => array('_field_encrypt_field_settings_validate'),
    '#tree' => TRUE,

    'encrypt' => array(
      '#type' => 'checkbox',
      '#title' => t('Encrypt this field'),
      '#default_value' => $form_state['field_encrypt']['encrypt'],
      '#weight' => 0,
  ),

    'phrase' => array(
      '#type' => 'textfield',
      '#title' => t('Encryption phrase'),
      '#description' => t('Field-specific phrase to use during the encoding process for this field.'),
      '#default_value' => $form_state['field_encrypt']['phrase'],
      '#weight' => 1,
      '#states' => array(
        'visible' => array(
          'input[name="field[settings][field_encrypt][encrypt]"]' => array('checked' => TRUE),
  ),
  ),
  ),
    '#weight' => -2,
  );

  // Hide the option from non-privileged users,
  // but ensure the values carried through
  if (!user_access(FIELD_ENCRYPT_PERMISSION)) {
    $field_encrypt =& $settings['field_encrypt'];
    foreach (array('encrypt', 'phrase') as $field_index) {
      $field_encrypt[$field_index]['#type'] = 'value';
      $field_encrypt[$field_index]['#value'] = $field_encrypt[$field_index]['#default_value'];
    }
  }

  // Make sure this file is loaded with this form
  form_load_include($form_state, 'inc', 'field_encrypt', 'field_encrypt.admin');

  // Add a submit handler to deal with the situation where
  // field encryption has been switched on or off.
  $form['#submit'][] = '_field_encrypt_field_settings_submit';
}

function _field_encrypt_field_settings_validate($element, &$form_state) {
  if ($element['encrypt']['#value'] && !$element['phrase']['#value']) {
    form_error($element['phrase'], t('You must provide an encryption phrase if you want to encrypt this field.'));
  }
}

function _field_encrypt_field_settings_submit($form, &$form_state) {
  $field_info = $form_state['field_encrypt']['field_info'];
  $old_encrypt = $form_state['field_encrypt']['encrypt'];
  $old_phrase = $form_state['field_encrypt']['phrase'];

  $values =& $form_state['values']['field']['settings']['field_encrypt'];
  $new_encrypt = $values['encrypt'];
  $new_phrase = $values['phrase'];

  if ($old_encrypt) {
    if ($new_encrypt) {
      // encryption flag still set, has the phrase changed?
      if ($new_phrase == $old_phrase) {
        // phrase is the same too, do nothing
      }
      else {
        // phrase has changed so need to re-encrypt the field
        module_load_include('inc', 'field_encrypt');
        field_encrypt_re_encrypt($field_info, $new_phrase);
      }
    }
    else {
      // was encrypted but now unencrypted, so unencrypt it
      module_load_include('inc', 'field_encrypt');
      field_encrypt_un_encrypt($field_info, $old_phrase);
    }
  }
  else {
    if ($new_encrypt) {
      // encryption flag wasn't set, but is now
      module_load_include('inc', 'field_encrypt');
      field_encrypt_do_encrypt($field_info, $new_phrase);
    }
    else {
      // encryption wasn't set, and still isn't, do nothing.
    }
  }
}