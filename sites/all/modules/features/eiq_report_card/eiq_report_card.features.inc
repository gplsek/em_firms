<?php
/**
 * @file
 * eiq_report_card.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function eiq_report_card_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function eiq_report_card_node_info() {
  $items = array(
    'report_card' => array(
      'name' => t('Report Card'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
