<?php
/**
 * @file
 * core_ef.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function core_ef_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'about';
  $context->description = '';
  $context->tag = 'Page Specific';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'about*' => 'about*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-menu-about' => array(
          'module' => 'menu',
          'delta' => 'menu-about',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Page Specific');
  $export['about'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'contact_info';
  $context->description = '';
  $context->tag = 'content';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'contact' => 'contact',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-menu-about' => array(
          'module' => 'menu',
          'delta' => 'menu-about',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
        'nodeblock-35' => array(
          'module' => 'nodeblock',
          'delta' => '35',
          'region' => 'sidebar_first',
          'weight' => '-9',
        ),
        'locationmap-image' => array(
          'module' => 'locationmap',
          'delta' => 'image',
          'region' => 'content',
          'weight' => '-28',
        ),
        'block-8' => array(
          'module' => 'block',
          'delta' => '8',
          'region' => 'content',
          'weight' => '-27',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('content');
  $export['contact_info'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'facebook_like';
  $context->description = '';
  $context->tag = 'sidebar2';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'theme-features' => 'theme-features',
        '7-different-home-pages' => '7-different-home-pages',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'widgets-s_facebook-like-box' => array(
          'module' => 'widgets',
          'delta' => 's_facebook-like-box',
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('sidebar2');
  $export['facebook_like'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'features_sidebar2';
  $context->description = '';
  $context->tag = 'sidebar2';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'page-right-sidebar' => 'page-right-sidebar',
        'theme-features' => 'theme-features',
        '7-different-home-pages' => '7-different-home-pages',
        'products-portfolios' => 'products-portfolios',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-e910204ced4d19c442af076fca7bda38' => array(
          'module' => 'views',
          'delta' => 'e910204ced4d19c442af076fca7bda38',
          'region' => 'sidebar_second',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('sidebar2');
  $export['features_sidebar2'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'footer';
  $context->description = '';
  $context->tag = 'sitewide';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-menu-footer' => array(
          'module' => 'menu',
          'delta' => 'menu-footer',
          'region' => 'bottom',
          'weight' => '-10',
        ),
        'widgets-s_socialmedia_profile-default' => array(
          'module' => 'widgets',
          'delta' => 's_socialmedia_profile-default',
          'region' => 'bottom',
          'weight' => '-9',
        ),
        'core_ef-footer-trust-block' => array(
          'module' => 'core_ef',
          'delta' => 'footer-trust-block',
          'region' => 'bottom',
          'weight' => '-8',
        ),
        'block-7' => array(
          'module' => 'block',
          'delta' => '7',
          'region' => 'bottom',
          'weight' => '-7',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('sitewide');
  $export['footer'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'how_it_works';
  $context->description = '';
  $context->tag = 'Page Specific';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'how-it-works*' => 'how-it-works*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-menu-how-it-works' => array(
          'module' => 'menu',
          'delta' => 'menu-how-it-works',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Page Specific');
  $export['how_it_works'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'hp_content';
  $context->description = '';
  $context->tag = 'homepage';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
        'home-variant-*' => 'home-variant-*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-earlyiq_slideshow_block-block' => array(
          'module' => 'views',
          'delta' => 'earlyiq_slideshow_block-block',
          'region' => 'highlighted',
          'weight' => '-10',
        ),
        'views-seven_features_block-block' => array(
          'module' => 'views',
          'delta' => 'seven_features_block-block',
          'region' => 'highlighted',
          'weight' => '-9',
        ),
        'nodeblock-35' => array(
          'module' => 'nodeblock',
          'delta' => '35',
          'region' => 'highlighted',
          'weight' => '-8',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('homepage');
  $export['hp_content'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'hp_slideshow5';
  $context->description = '';
  $context->tag = 'homepage';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'home-variant-5' => 'home-variant-5',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-seven_slideshow_5-block' => array(
          'module' => 'views',
          'delta' => 'seven_slideshow_5-block',
          'region' => 'highlighted',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('homepage');
  $export['hp_slideshow5'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'hp_slideshow7';
  $context->description = '';
  $context->tag = 'homepage';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'home-variant-7' => 'home-variant-7',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-seven_slideshow_7-block' => array(
          'module' => 'views',
          'delta' => 'seven_slideshow_7-block',
          'region' => 'highlighted',
          'weight' => '-28',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('homepage');
  $export['hp_slideshow7'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'main_menu';
  $context->description = '';
  $context->tag = 'sitewide';
  $context->conditions = array(
    'context' => array(
      'values' => array(
        '~eiq_commerce' => '~eiq_commerce',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'system-main-menu' => array(
          'module' => 'system',
          'delta' => 'main-menu',
          'region' => 'header',
          'weight' => '-9',
        ),
        'jump_menu-jump_menu-m_main-menu' => array(
          'module' => 'jump_menu',
          'delta' => 'jump_menu-m_main-menu',
          'region' => 'header',
          'weight' => '-8',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('sitewide');
  $export['main_menu'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'markets';
  $context->description = '';
  $context->tag = 'Page Specific';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'markets*' => 'markets*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-menu-markets' => array(
          'module' => 'menu',
          'delta' => 'menu-markets',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Page Specific');
  $export['markets'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'masquerade';
  $context->description = '';
  $context->tag = 'sitewide';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'masquerade-masquerade' => array(
          'module' => 'masquerade',
          'delta' => 'masquerade',
          'region' => 'footer',
          'weight' => '9',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('sitewide');
  $export['masquerade'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'product_portfolio_intro';
  $context->description = '';
  $context->tag = 'content';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'portfolio-*' => 'portfolio-*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'block-5' => array(
          'module' => 'block',
          'delta' => '5',
          'region' => 'content',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('content');
  $export['product_portfolio_intro'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'products';
  $context->description = '';
  $context->tag = 'Page Specific';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'products*' => 'products*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-menu-products' => array(
          'module' => 'menu',
          'delta' => 'menu-products',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Page Specific');
  $export['products'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'sidebar_detail_pages';
  $context->description = '';
  $context->tag = 'Sidebar 1';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'what-we-do*' => 'what-we-do*',
        'how-it-works*' => 'how-it-works*',
        'products*' => 'products*',
        'about*' => 'about*',
        'contact*' => 'contact*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'nodeblock-35' => array(
          'module' => 'nodeblock',
          'delta' => '35',
          'region' => 'sidebar_first',
          'weight' => '-7',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Sidebar 1');
  $export['sidebar_detail_pages'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'teasers_main_constituents';
  $context->description = '';
  $context->tag = 'sidebar1';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'typography-features' => 'typography-features',
        'blog/*' => 'blog/*',
        'blog' => 'blog',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-seven_features_side_block-block' => array(
          'module' => 'views',
          'delta' => 'seven_features_side_block-block',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('sidebar1');
  $export['teasers_main_constituents'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'user_menu';
  $context->description = '';
  $context->tag = 'sitewide';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'system-user-menu' => array(
          'module' => 'system',
          'delta' => 'user-menu',
          'region' => 'header',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('sitewide');
  $export['user_menu'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'what_we_do';
  $context->description = '';
  $context->tag = 'Page Specific';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'what-we-do*' => 'what-we-do*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-menu-what-we-do' => array(
          'module' => 'menu',
          'delta' => 'menu-what-we-do',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
      ),
    ),
    'menu' => 'node/36',
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Page Specific');
  $export['what_we_do'] = $context;

  return $export;
}
