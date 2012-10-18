<?php
/**
 * @file
 * core_ef.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function core_ef_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => '2',
  );

  // Exported role: co_admin.
  $roles['co_admin'] = array(
    'name' => 'co_admin',
    'weight' => '4',
  );

  // Exported role: co_user.
  $roles['co_user'] = array(
    'name' => 'co_user',
    'weight' => '3',
  );

  return $roles;
}
