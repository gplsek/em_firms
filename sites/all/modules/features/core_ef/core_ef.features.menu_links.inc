<?php
/**
 * @file
 * core_ef.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function core_ef_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu:node/36
  $menu_links['main-menu:node/36'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/36',
    'router_path' => 'node/%',
    'link_title' => 'What We Do',
    'options' => array(
      'minipanel' => 'what_we_do_minipanel',
      'menu_minipanels_hover' => array(
        'position' => array(
          'target' => 'false',
          'target_custom' => '',
          'type' => 'absolute',
          'corner' => array(
            'target' => 'bottomLeft',
            'tooltip' => 'topLeft',
          ),
        ),
        'show' => array(
          'delay' => '90',
          'when' => array(
            'event' => 'mouseover',
          ),
          'effect' => array(
            'type' => 'slide',
            'length' => '100',
          ),
        ),
        'hide' => array(
          'delay' => '100',
          'effect' => array(
            'type' => 'slide',
            'length' => '100',
          ),
        ),
        'style' => array(
          'name' => 'light',
          'width' => array(
            'min' => '0',
            'max' => '250',
          ),
          'border' => array(
            'width' => '0',
            'color' => '#d3d3d3',
            'radius' => '0',
          ),
          'tip' => 'none',
        ),
        'mlid' => '1213',
      ),
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '1',
    'weight' => '-45',
  );
  // Exported menu link: main-menu:node/40
  $menu_links['main-menu:node/40'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/40',
    'router_path' => 'node/%',
    'link_title' => 'How it Works',
    'options' => array(
      'minipanel' => 'how_it_works_minipanel',
      'menu_minipanels_hover' => array(
        'position' => array(
          'target' => 'false',
          'target_custom' => '',
          'type' => 'absolute',
          'corner' => array(
            'target' => 'bottomLeft',
            'tooltip' => 'topLeft',
          ),
        ),
        'show' => array(
          'delay' => '90',
          'when' => array(
            'event' => 'mouseover',
          ),
          'effect' => array(
            'type' => 'slide',
            'length' => '100',
          ),
        ),
        'hide' => array(
          'delay' => '100',
          'effect' => array(
            'type' => 'slide',
            'length' => '100',
          ),
        ),
        'style' => array(
          'name' => 'light',
          'width' => array(
            'min' => '0',
            'max' => '250',
          ),
          'border' => array(
            'width' => '0',
            'color' => '#d3d3d3',
            'radius' => '0',
          ),
          'tip' => 'none',
        ),
        'mlid' => '1217',
      ),
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '1',
    'weight' => '-44',
  );
  // Exported menu link: main-menu:node/45
  $menu_links['main-menu:node/45'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/45',
    'router_path' => 'node/%',
    'link_title' => 'Products',
    'options' => array(
      'minipanel' => 'products_minipanel',
      'menu_minipanels_hover' => array(
        'position' => array(
          'target' => 'false',
          'target_custom' => '',
          'type' => 'absolute',
          'corner' => array(
            'target' => 'bottomLeft',
            'tooltip' => 'topLeft',
          ),
        ),
        'show' => array(
          'delay' => '90',
          'when' => array(
            'event' => 'mouseover',
          ),
          'effect' => array(
            'type' => 'slide',
            'length' => '100',
          ),
        ),
        'hide' => array(
          'delay' => '100',
          'effect' => array(
            'type' => 'slide',
            'length' => '100',
          ),
        ),
        'style' => array(
          'name' => 'light',
          'width' => array(
            'min' => '0',
            'max' => '250',
          ),
          'border' => array(
            'width' => '0',
            'color' => '#d3d3d3',
            'radius' => '0',
          ),
          'tip' => 'none',
        ),
        'mlid' => '1222',
      ),
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '1',
    'weight' => '-43',
  );
  // Exported menu link: main-menu:node/54
  $menu_links['main-menu:node/54'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/54',
    'router_path' => 'node/%',
    'link_title' => 'Company',
    'options' => array(
      'minipanel' => 'about_minipanel',
      'menu_minipanels_hover' => array(
        'position' => array(
          'target' => 'false',
          'target_custom' => '',
          'type' => 'absolute',
          'corner' => array(
            'target' => 'bottomLeft',
            'tooltip' => 'topLeft',
          ),
        ),
        'show' => array(
          'delay' => '90',
          'when' => array(
            'event' => 'mouseover',
          ),
          'effect' => array(
            'type' => 'slide',
            'length' => '100',
          ),
        ),
        'hide' => array(
          'delay' => '100',
          'effect' => array(
            'type' => 'slide',
            'length' => '100',
          ),
        ),
        'style' => array(
          'name' => 'light',
          'width' => array(
            'min' => '0',
            'max' => '250',
          ),
          'border' => array(
            'width' => '0',
            'color' => '#d3d3d3',
            'radius' => '0',
          ),
          'tip' => 'none',
        ),
        'mlid' => '1231',
      ),
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '1',
    'weight' => '-41',
  );
  // Exported menu link: user-menu:<front>
  $menu_links['user-menu:<front>'] = array(
    'menu_name' => 'user-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Log in',
    'options' => array(
      'menu_token_link_path' => 'user/login?destination=[current-page:url:path]',
      'menu_token_data' => array(),
      'menu_token_options' => array(
        'clear' => 0,
      ),
      'alter' => TRUE,
      'attributes' => array(),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '1',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
  );
  // Exported menu link: user-menu:user
  $menu_links['user-menu:user'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'User account',
    'options' => array(
      'alter' => TRUE,
    ),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-10',
  );
  // Exported menu link: user-menu:user/logout
  $menu_links['user-menu:user/logout'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Log out',
    'options' => array(
      'alter' => TRUE,
    ),
    'module' => 'system',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '10',
  );
  // Exported menu link: user-menu:user/register
  $menu_links['user-menu:user/register'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/register',
    'router_path' => 'user/register',
    'link_title' => 'Create new account',
    'options' => array(),
    'module' => 'system',
    'hidden' => '-1',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '0',
    'parent_path' => 'user',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Company');
  t('Create new account');
  t('How it Works');
  t('Log in');
  t('Log out');
  t('Products');
  t('User account');
  t('What We Do');


  return $menu_links;
}
