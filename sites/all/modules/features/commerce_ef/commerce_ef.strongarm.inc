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
  $strongarm->value = array();
  $export['commerce_node_checkout_products_data_company'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rules_empty_sets';
  $strongarm->value = array(
    'commerce_cart_product_prepare' => 0,
    'commerce_payment_order_paid_in_full' => 1,
    'commerce_customer_profile_insert' => 2,
    'commerce_customer_profile_update' => 3,
    'commerce_customer_profile_presave' => 4,
    'commerce_customer_profile_delete' => 5,
    'commerce_customer_profile_view' => 6,
    'commerce_line_item_insert' => 7,
    'commerce_line_item_update' => 8,
    'commerce_line_item_presave' => 9,
    'commerce_line_item_delete' => 10,
    'commerce_line_item_view' => 11,
    'commerce_order_insert' => 12,
    'commerce_order_update' => 13,
    'commerce_order_presave' => 14,
    'commerce_order_delete' => 15,
    'commerce_order_view' => 16,
    'commerce_payment_transaction_insert' => 17,
    'commerce_payment_transaction_update' => 18,
    'commerce_payment_transaction_presave' => 19,
    'commerce_payment_transaction_delete' => 20,
    'commerce_payment_transaction_view' => 21,
    'commerce_product_insert' => 22,
    'commerce_product_update' => 23,
    'commerce_product_presave' => 24,
    'commerce_product_delete' => 25,
    'commerce_product_view' => 26,
    'field_collection_item_insert' => 27,
    'field_collection_item_update' => 28,
    'field_collection_item_presave' => 29,
    'field_collection_item_delete' => 30,
    'field_collection_item_view' => 31,
    'node_insert' => 32,
    'node_update' => 33,
    'node_presave' => 34,
    'node_view' => 35,
    'node_delete' => 36,
    'init' => 37,
    'cron' => 38,
    'watchdog' => 39,
    'user_insert' => 40,
    'user_update' => 41,
    'user_presave' => 42,
    'user_view' => 43,
    'user_delete' => 44,
    'user_login' => 45,
    'user_logout' => 46,
    'comment_insert' => 47,
    'comment_update' => 48,
    'comment_presave' => 49,
    'comment_view' => 50,
    'comment_delete' => 51,
    'taxonomy_term_insert' => 52,
    'taxonomy_term_update' => 53,
    'taxonomy_term_presave' => 54,
    'taxonomy_term_delete' => 55,
    'taxonomy_vocabulary_insert' => 56,
    'taxonomy_vocabulary_update' => 57,
    'taxonomy_vocabulary_presave' => 58,
    'taxonomy_vocabulary_delete' => 59,
  );
  $export['rules_empty_sets'] = $strongarm;

  return $export;
}
