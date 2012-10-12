<?php
/**
 * @file
 * core_ef.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function core_ef_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_company|node|data_company|form';
  $field_group->group_name = 'group_company';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'data_company';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Company Information',
    'weight' => '2',
    'children' => array(
      0 => 'body',
      1 => 'field_phone',
      2 => 'field_address',
      3 => 'field_fein',
      4 => 'field_website',
      5 => 'field_company_type',
      6 => 'field_state_of_incorp',
      7 => 'field_state_of_registration',
      8 => 'field_year_of_legal_formation',
      9 => 'field_dba',
      10 => 'title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Company Information',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_company|node|data_company|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_constituents|node|data_company|form';
  $field_group->group_name = 'group_constituents';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'data_company';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Constituents',
    'weight' => '12',
    'children' => array(
      0 => 'field_officers',
      1 => 'field_constituents',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Constituents',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_constituents|node|data_company|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_pii|field_collection_item|field_constituents|form';
  $field_group->group_name = 'group_pii';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_constituents';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Personal Information',
    'weight' => '7',
    'children' => array(
      0 => 'field_dob',
      1 => 'field_citizenship',
      2 => 'field_driver_license',
      3 => 'field_ssn',
      4 => 'field_address',
      5 => 'field_employment',
      6 => 'field_education',
      7 => 'field_criminal',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Personal Information',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_pii|field_collection_item|field_constituents|form'] = $field_group;

  return $export;
}
