<?php
/**
 * @file
 * eiq_partners.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eiq_partners_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function eiq_partners_node_info() {
  $items = array(
    'partner' => array(
      'name' => t('Partner'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Partner Name'),
      'help' => '',
    ),
  );
  return $items;
}
