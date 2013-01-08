<?php
/**
 * @file
 * Contains theme override functions and preprocess functions for the theme.
 *
 * ABOUT THE TEMPLATE.PHP FILE
 *
 *   The template.php file is one of the most useful files when creating or
 *   modifying Drupal themes. You can modify or override Drupal's theme
 *   functions, intercept or make additional variables available to your theme,
 *   and create custom PHP logic. For more information, please visit the Theme
 *   Developer's Guide on Drupal.org: http://drupal.org/theme-guide
 *
 * OVERRIDING THEME FUNCTIONS
 *
 *   The Drupal theme system uses special theme functions to generate HTML
 *   output automatically. Often we wish to customize this HTML output. To do
 *   this, we have to override the theme function. You have to first find the
 *   theme function that generates the output, and then "catch" it and modify it
 *   here. The easiest way to do it is to copy the original function in its
 *   entirety and paste it here, changing the prefix from theme_ to STARTERKIT_.
 *   For example:
 *
 *     original: theme_breadcrumb()
 *     theme override: STARTERKIT_breadcrumb()
 *
 *   where STARTERKIT is the name of your sub-theme. For example, the
 *   zen_classic theme would define a zen_classic_breadcrumb() function.
 *
 *   If you would like to override either of the two theme functions used in Zen
 *   core, you should first look at how Zen core implements those functions:
 *     theme_breadcrumbs()      in zen/template.php
 *     theme_menu_local_tasks() in zen/template.php
 *
 *   For more information, please visit the Theme Developer's Guide on
 *   Drupal.org: http://drupal.org/node/173880
 *
 * CREATE OR MODIFY VARIABLES FOR YOUR THEME
 *
 *   Each tpl.php template file has several variables which hold various pieces
 *   of content. You can modify those variables (or add new ones) before they
 *   are used in the template files by using preprocess functions.
 *
 *   This makes THEME_preprocess_HOOK() functions the most powerful functions
 *   available to themers.
 *
 *   It works by having one preprocess function for each template file or its
 *   derivatives (called template suggestions). For example:
 *     THEME_preprocess_page    alters the variables for page.tpl.php
 *     THEME_preprocess_node    alters the variables for node.tpl.php or
 *                              for node-forum.tpl.php
 *     THEME_preprocess_comment alters the variables for comment.tpl.php
 *     THEME_preprocess_block   alters the variables for block.tpl.php
 *
 *   For more information on preprocess functions and template suggestions,
 *   please visit the Theme Developer's Guide on Drupal.org:
 *   http://drupal.org/node/223440
 *   and http://drupal.org/node/190815#template-suggestions
 */


/**
 * Override or insert variables into the html templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("html" in this case.)
 */
function earlyiq_preprocess_html(&$variables, $hook) {
  //$variables['sample_variable'] = t('Lorem ipsum.');

  // The body tag's classes are controlled by the $classes_array variable. To
  // remove a class from $classes_array, use array_diff().
  //$variables['classes_array'] = array_diff($variables['classes_array'], array('class-to-remove'));
  if (context_isset('eiq_commerce', 'partner')) {
    $variables['classes_array'][] = 'partner-' . context_get('eiq_commerce', 'partner');
  }
}

/**
 * Override or insert variables into the page templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("page" in this case.)
 */
function earlyiq_preprocess_page(&$variables, $hook) {
  //dpm($variables['node']);
  //$variables['logo'] = str_replace('default/files/', 'default/files/styles/logo/public/', $variables['logo']);
  $variables['logo_images'] =  '<a href="/" title="Home" rel="home" id="logo"><img src="' . $variables['logo'] . '" alt="Home" /></a><a href="/" title="Home" rel="home" id="mobile-logo"><img src="' . $variables['logo'] . '" alt="Home" /></a>';
  $partner = context_get('eiq_commerce', 'partner') ? context_get('eiq_commerce', 'partner') : 'client';
  switch ($partner) {
    case 'kiva-zip':
      $variables['logo_images'] = '<a href="/" title="Partner" rel="partner" id="logo-partner"><img src="/sites/all/themes/earlyiq/images/partners/logo-kiva-zip.png" alt="Partner" /></a><a href="/" title="Home" rel="home" id="eiq-logo"><img src="' . $variables['logo'] . '" alt="Home" /></a>';
      break;
  }
  if (context_isset('eiq_commerce', 'partner')) {
    $variables['main_menu'] = '';
    $variables['main_menu_jump'] = '';
  } else {
    //$variables['main-menu'] = drupal_render($block_main['content']) . drupal_render($block_jump['content']);
    $variables['main_menu'] = module_invoke('system', 'block_view', 'main-menu');
    $variables['main_menu_jump'] = module_invoke('jump_menu', 'block_view', 'jump_menu-m_main-menu');
  }
<<<<<<< HEAD
  if ((arg(0) == "user" && arg(1) == "reset") || (isset($variables['node']) && $variables['node']->type == 'data_person') || (arg(1) == "validation")) {
    $variables['show_steps'] = '<div id="show-steps"><span id="step1"></span><span id="step2"></span><span id="step3"></span></div>';
  }
=======
  if (arg(0) == "user" && (arg(1) == "reset" || (arg(2) == 'edit' && isset($_GET['pass-reset-token'])))) {
    $variables['show_steps'] = '<div id="show-steps"><div class="show-steps-inner"><span id="step1" class="activeStep">Step 1</span><span id="step2">Step 2</span><span id="step3">Step 3</span></div></div>';

  } else if (isset($variables['node']) && $variables['node']->type == 'data_person') {
    $variables['show_steps'] = '<div id="show-steps"><div class="show-steps-inner"><span id="step1" class="activeStep">Step 1</span><span id="step2" class="activeStep">Step 2</span><span id="step3">Step 3</span></div></div>';
>>>>>>> master

  } else if (arg(0) == "validation") {
    $variables['show_steps'] = '<div id="show-steps"><div class="show-steps-inner"><span id="step1" class="activeStep">Step 1</span><span id="step2" class="activeStep">Step 2</span><span id="step3" class="activeStep">Step 3</span></div></div>';
  }
}


/**
 * Override or insert variables into the node templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("node" in this case.)
 */
/* -- Delete this line if you want to use this function
function STARTERKIT_preprocess_node(&$variables, $hook) {
  $variables['sample_variable'] = t('Lorem ipsum.');

  // Optionally, run node-type-specific preprocess functions, like
  // STARTERKIT_preprocess_node_page() or STARTERKIT_preprocess_node_story().
  $function = __FUNCTION__ . '_' . $variables['node']->type;
  if (function_exists($function)) {
    $function($variables, $hook);
  }
}
// */

/**
 * Override or insert variables into the comment templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("comment" in this case.)
 */
/* -- Delete this line if you want to use this function
function STARTERKIT_preprocess_comment(&$variables, $hook) {
  $variables['sample_variable'] = t('Lorem ipsum.');
}
// */

/**
 * Override or insert variables into the block templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
/* -- Delete this line if you want to use this function
function STARTERKIT_preprocess_block(&$variables, $hook) {
  // Add a count to all the blocks in the region.
  $variables['classes_array'][] = 'count-' . $variables['block_id'];
}
// */



/**
 *  Theme override for theme_form_element_label
 */
function earlyiq_form_element_label(&$variables) {
  $element = $variables['element'];
  if (isset($element['#field_name'])) {
    switch ($element['#field_name']) {
      case 'field_name_last':
        $help_txt = "Enter your full legal name. No aliases, nicknames, or other names or references.";
        break;
      case 'field_ssn':
        $help_txt = "Enter your U.S. Social Security Number. This information will be validated and cross referenced to ensure it matches your name and date of birth.";
        break;
      case 'field_convictions':
        $help_txt = "<p>Answer “yes” if you have any criminal convictions regardless of date, level (state or Federal), or severity (misdemeanor or felony). This does not include traffic violations (speeding, etc.) but does include convictions for DUI or similar motor vehicle convictions. Answer “no” if you have no criminal convictions.</p><p>For each conviction, enter the county and state in which you were convicted. If you have more than one conviction,
use the Add Another button to enter additional convictions.</p>";
        break;
   }
  }
<<<<<<< HEAD
  $help_icon = isset($help_txt) ? '<span class="help-icon"><img src="/' . drupal_get_path('theme', 'earlyiq') . '/images/icon_form-more-info.png"></span><span class="help-info">' . $help_txt . '</span>' : '';
=======
  $help_icon = isset($help_txt) ? '<div class="field-description"><span class="help-icon"><img src="/' . drupal_get_path('theme', 'earlyiq') . '/images/icon_form-more-info.png"></span><span class="help-info">' . $help_txt . '</span></div>' : '';
>>>>>>> master
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // If title and required marker are both empty, output no label.
  if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
    return '';
  }

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $title = filter_xss_admin($element['#title']);

  $attributes = array();
  // Style the label as class option to display inline with the element.
  if ($element['#title_display'] == 'after') {
    $attributes['class'] = 'option';
  }
  // Show label only to screen readers to avoid disruption in visual flows.
  elseif ($element['#title_display'] == 'invisible') {
    $attributes['class'] = 'element-invisible';
  }

  if (!empty($element['#id'])) {
    $attributes['for'] = $element['#id'];
  }

  // The leading whitespace helps visually separate fields from inline labels.
  return ' <label' . drupal_attributes($attributes) . '>' . $t('!title !required !help', array('!title' => $title, '!required' => $required, '!help' => $help_icon)) . "</label>\n";
}


/**
 *  Theme override for theme_fieldset
 */
function earlyiq_fieldset($variables) {
  $element = $variables['element'];
  if (isset($element['#title'])) {
    switch (trim($element['#title'])) {
      case 'Date of Birth':
        $help_txt = "Enter your data of birth in MM/DD/YYYY format.";
        break;
      case 'Address':
        $help_txt = "Enter your current physical address. No P.O. Boxes, or other mailing service addresses are allowed. Only U.S. addresses are allowed.";
        break;
    }
  }
<<<<<<< HEAD
  $help_icon = isset($help_txt) ? '<span class="help-icon"><img src="/' . drupal_get_path('theme', 'earlyiq') . '/images/icon_form-more-info.png"></span><span class="help-info">' . $help_txt . '</span>' : '';
=======
  $help_icon = isset($help_txt) ? '<div class="field-description"><span class="help-icon"><img src="/' . drupal_get_path('theme', 'earlyiq') . '/images/icon_form-more-info.png"></span><span class="help-info">' . $help_txt . '</span></div>' : '';
>>>>>>> master
  element_set_attributes($element, array('id'));
  _form_set_class($element, array('form-wrapper'));

  $output = '<fieldset' . drupal_attributes($element['#attributes']) . '>';
  if (!empty($element['#title'])) {
    // Always wrap fieldset legends in a SPAN for CSS positioning.
    $output .= '<legend><span class="fieldset-legend">' . $element['#title'] . $help_icon .  '</span></legend>';
  }
  $output .= '<div class="fieldset-wrapper">';
  if (!empty($element['#description'])) {
    $output .= '<div class="fieldset-description">' . $element['#description'] . '</div>';
  }
  $output .= $element['#children'];
  if (isset($element['#value'])) {
    $output .= $element['#value'];
  }
  $output .= '</div>';
  $output .= "</fieldset>\n";
  return $output;
}

