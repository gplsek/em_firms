<?php
/**
 * @file
 * core_ef.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function core_ef_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function core_ef_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function core_ef_node_info() {
  $items = array(
    'data_company' => array(
      'name' => t('Data Company'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Company Name'),
      'help' => '',
    ),
    'page' => array(
      'name' => t('Basic page'),
      'base' => 'node_content',
      'description' => t('Use <em>basic pages</em> for your static content, such as an \'About us\' page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'seven_client' => array(
      'name' => t('Seven - Client'),
      'base' => 'node_content',
      'description' => t('A Client is a logo or image representation you can use to backup your site reputation and scale. It\'s very usefull to provide a solid guarantee of your work.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
    'seven_home_item_block' => array(
      'name' => t('Seven - Home Item Block'),
      'base' => 'node_content',
      'description' => t('The blocks that are shown after the Slideshow with an icon.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'seven_product' => array(
      'name' => t('Seven - Product'),
      'base' => 'node_content',
      'description' => t('A Product content type is special for <strong>Products, Items, Portfolio Elements, Projects and any other stuff you want to showcase</strong>.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'seven_slideshow_item' => array(
      'name' => t('Seven - SlideShow Item'),
      'base' => 'node_content',
      'description' => t('This content type is completelly compatible with all 7 Slideshows. You can define: <strong>a title</strong>, <strong>a description</strong> and <strong>the URL the link will go to.</strong>'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
