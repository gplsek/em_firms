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
      1 => 'field_company_type',
      2 => 'field_dba',
      3 => 'field_fein',
      4 => 'field_website',
      5 => 'field_year_of_legal_formation',
      6 => 'field_company_address',
      7 => 'field_company_phone',
      8 => 'field_facebook',
      9 => 'field_linkedin',
      10 => 'field_state_incorp',
      11 => 'field_state_registration',
      12 => 'field_twitter',
      13 => 'title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Company Information',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsible',
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
    'label' => 'Officers',
    'weight' => '4',
    'children' => array(
      0 => 'field_invite_officers',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Officers',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_constituents|node|data_company|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_personal_info|node|data_person|form';
  $field_group->group_name = 'group_personal_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'data_person';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Personal Information',
    'weight' => '11',
    'children' => array(
      0 => 'field_driver_license',
      1 => 'field_citizenship',
      2 => 'field_linkedin_profile',
      3 => 'field_address',
      4 => 'field_employment',
      5 => 'field_education',
      6 => 'field_criminal_convictions',
      7 => 'field_criminal',
      8 => 'field_civil',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_personal_info|node|data_person|form'] = $field_group;

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
      0 => 'field_employment',
      1 => 'field_address',
      2 => 'field_citizenship',
      3 => 'field_criminal',
      4 => 'field_driver_license',
      5 => 'field_education',
      6 => 'field_linkedin_profile',
      7 => 'field_agree_final',
      8 => 'field_civil',
      9 => 'field_criminal_convictions',
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
