<?php
/**
 * @file
 * commerce_ef.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_ef_default_rules_configuration() {
  $items = array();
  $items['rules_add_to_cart_and_go_straight_to_checkout'] = entity_import('rules_config', '{ "rules_add_to_cart_and_go_straight_to_checkout" : {
      "LABEL" : "add to cart and go straight to checkout",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "earlyiq" ],
      "REQUIRES" : [ "rules", "commerce_cart" ],
      "ON" : [ "commerce_cart_product_add" ],
      "DO" : [ { "redirect" : { "url" : "cart\\/checkout" } } ]
    }
  }');
  return $items;
}
