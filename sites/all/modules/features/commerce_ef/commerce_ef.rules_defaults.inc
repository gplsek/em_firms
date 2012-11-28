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
      "LABEL" : "after add to cart go straight to checkout NOT FREE",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "earlyiq" ],
      "REQUIRES" : [ "commerce_payment", "rules", "commerce_cart" ],
      "ON" : [ "commerce_cart_product_add" ],
      "IF" : [
        { "commerce_payment_order_balance_comparison" : {
            "commerce_order" : [ "commerce_order" ],
            "operator" : "\\u003E",
            "value" : "0"
          }
        }
      ],
      "DO" : [ { "redirect" : { "url" : "checkout\\/[commerce-order:order-id]" } } ]
    }
  }');
  $items['rules_after_add_to_cart_go_straight_to_checkout_free'] = entity_import('rules_config', '{ "rules_after_add_to_cart_go_straight_to_checkout_free" : {
      "LABEL" : "after add to cart go straight to checkout FREE",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "TAGS" : [ "earlyiq" ],
      "REQUIRES" : [ "commerce_payment", "commerce_checkout", "commerce_cart" ],
      "ON" : [ "commerce_cart_product_add" ],
      "IF" : [
        { "commerce_payment_order_balance_comparison" : { "commerce_order" : [ "commerce_order" ], "value" : "0" } }
      ],
      "DO" : [
        { "commerce_checkout_complete" : { "commerce_order" : [ "commerce_order" ] } }
      ]
    }
  }');
  $items['rules_after_add_to_cart_go_straight_to_checkout_free_cloned_'] = entity_import('rules_config', '{ "rules_after_add_to_cart_go_straight_to_checkout_free_cloned_" : {
      "LABEL" : "after add to cart go straight to checkout FREE (cloned)",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "earlyiq" ],
      "REQUIRES" : [ "commerce_payment", "rules", "commerce_cart" ],
      "ON" : [ "commerce_cart_product_add" ],
      "IF" : [
        { "commerce_payment_order_balance_comparison" : { "commerce_order" : [ "commerce_order" ], "value" : "0" } }
      ],
      "DO" : [ { "redirect" : { "url" : "checkout\\/[commerce-order:order-id]" } } ]
    }
  }');
  $items['rules_company_app_save_to_checkout'] = entity_import('rules_config', '{ "rules_company_app_save_to_checkout" : {
      "LABEL" : "company app save and add to cart",
      "PLUGIN" : "reaction rule",
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
  $items['rules_company_app_save_to_checkout_free'] = entity_import('rules_config', '{ "rules_company_app_save_to_checkout_free" : {
      "LABEL" : "company app save to checkout FREE",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "REQUIRES" : [ "rules", "commerce_payment", "commerce_cart" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "data_company" : "data_company" } }
          }
        },
        { "commerce_payment_order_balance_comparison" : { "commerce_order" : [ "site:current-cart-order" ], "value" : "0" } }
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
