<?php
/**
 * @file
 * commerce_ef.features.inc
 */

/**
 * Implements hook_commerce_product_default_types().
 */
function commerce_ef_commerce_product_default_types() {
  $items = array(
    'commerce_node_checkout' => array(
      'type' => 'commerce_node_checkout',
      'name' => 'Pay to Publish',
      'description' => 'A product associated with publishing a node.',
      'help' => '',
      'revision' => '1',
    ),
    'product' => array(
      'type' => 'product',
      'name' => 'Product',
      'description' => 'A basic product type.',
      'help' => '',
      'revision' => '1',
    ),
  );
  return $items;
}

/**
 * Implements hook_ctools_plugin_api().
 */
function commerce_ef_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
