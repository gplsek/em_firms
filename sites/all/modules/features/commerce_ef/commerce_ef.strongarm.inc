<?php
/**
 * @file
 * commerce_ef.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function commerce_ef_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'commerce_customer_profile_billing_field';
  $strongarm->value = 'commerce_customer_billing';
  $export['commerce_customer_profile_billing_field'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'commerce_node_checkout_products_data_company';
  $strongarm->value = array(
    0 => 1,
    1 => 2,
  );
  $export['commerce_node_checkout_products_data_company'] = $strongarm;

  return $export;
}
