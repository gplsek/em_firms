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
      "DO" : [ { "redirect" : { "url" : "checkout\\/[commerce-order:order-id]" } } ]
    }
  }');
  $items['rules_company_app_save_to_checkout'] = entity_import('rules_config', '{ "rules_company_app_save_to_checkout" : {
      "LABEL" : "company app save to checkout",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "9",
      "ACTIVE" : false,
      "REQUIRES" : [ "rules", "commerce_cart" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "data_company" : "data_company" } }
          }
        }
      ],
      "DO" : [
        { "commerce_cart_product_add_by_sku" : {
            "USING" : {
              "user" : [ "site:current-user" ],
              "sku" : "[node:field-product-id]",
              "quantity" : "1",
              "combine" : 1
            },
            "PROVIDE" : { "product_add_line_item" : { "product_add_line_item" : "Added product line item" } }
          }
        }
      ]
    }
  }');
  return $items;
}
