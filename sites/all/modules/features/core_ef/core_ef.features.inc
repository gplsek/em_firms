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
 * Implements hook_image_default_styles().
 */
function core_ef_image_default_styles() {
  $styles = array();

  // Exported image style: seven-blog.
  $styles['seven-blog'] = array(
    'name' => 'seven-blog',
    'effects' => array(
      20 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '611',
          'height' => '210',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: seven-features.
  $styles['seven-features'] = array(
    'name' => 'seven-features',
    'effects' => array(
      18 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => '52',
          'upscale' => 0,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: seven-our-clients.
  $styles['seven-our-clients'] = array(
    'name' => 'seven-our-clients',
    'effects' => array(
      3 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '140',
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: seven-our-clients-grayscale.
  $styles['seven-our-clients-grayscale'] = array(
    'name' => 'seven-our-clients-grayscale',
    'effects' => array(
      4 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '140',
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '1',
      ),
      5 => array(
        'label' => 'Desaturate',
        'help' => 'Desaturate converts an image to grayscale.',
        'effect callback' => 'image_desaturate_effect',
        'dimensions passthrough' => TRUE,
        'module' => 'image',
        'name' => 'image_desaturate',
        'data' => array(),
        'weight' => '2',
      ),
    ),
  );

  // Exported image style: seven-portfolio-1-column.
  $styles['seven-portfolio-1-column'] = array(
    'name' => 'seven-portfolio-1-column',
    'effects' => array(
      9 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '458',
          'height' => '208',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: seven-portfolio-2-columns.
  $styles['seven-portfolio-2-columns'] = array(
    'name' => 'seven-portfolio-2-columns',
    'effects' => array(
      7 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '452',
          'height' => '208',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: seven-portfolio-3-columns.
  $styles['seven-portfolio-3-columns'] = array(
    'name' => 'seven-portfolio-3-columns',
    'effects' => array(
      6 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '452',
          'height' => '208',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: seven-portfolio-colorbox.
  $styles['seven-portfolio-colorbox'] = array(
    'name' => 'seven-portfolio-colorbox',
    'effects' => array(
      8 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '452',
          'height' => '208',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: seven-portfolio-slideshow-fullscreen.
  $styles['seven-portfolio-slideshow-fullscreen'] = array(
    'name' => 'seven-portfolio-slideshow-fullscreen',
    'effects' => array(
      11 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '912',
          'height' => '400',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: seven-portfolio-slideshow-thumbnail.
  $styles['seven-portfolio-slideshow-thumbnail'] = array(
    'name' => 'seven-portfolio-slideshow-thumbnail',
    'effects' => array(
      10 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '127',
          'height' => '60',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: seven-product-colorbox.
  $styles['seven-product-colorbox'] = array(
    'name' => 'seven-product-colorbox',
    'effects' => array(
      22 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '1000',
          'height' => '1000',
          'upscale' => 0,
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: seven-product-node.
  $styles['seven-product-node'] = array(
    'name' => 'seven-product-node',
    'effects' => array(
      21 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '611',
          'height' => '300',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: seven-recent-articles.
  $styles['seven-recent-articles'] = array(
    'name' => 'seven-recent-articles',
    'effects' => array(
      23 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '50',
          'height' => '50',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: seven-recent-products.
  $styles['seven-recent-products'] = array(
    'name' => 'seven-recent-products',
    'effects' => array(
      2 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '452',
          'height' => '208',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: seven-slideshow-1.
  $styles['seven-slideshow-1'] = array(
    'name' => 'seven-slideshow-1',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '958',
          'height' => '311',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: seven-slideshow-2.
  $styles['seven-slideshow-2'] = array(
    'name' => 'seven-slideshow-2',
    'effects' => array(
      24 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '595',
          'height' => '318',
        ),
        'weight' => '2',
      ),
    ),
  );

  // Exported image style: seven-slideshow-3.
  $styles['seven-slideshow-3'] = array(
    'name' => 'seven-slideshow-3',
    'effects' => array(
      14 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '958',
          'height' => '311',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: seven-slideshow-4.
  $styles['seven-slideshow-4'] = array(
    'name' => 'seven-slideshow-4',
    'effects' => array(
      15 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '958',
          'height' => '311',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: seven-slideshow-5.
  $styles['seven-slideshow-5'] = array(
    'name' => 'seven-slideshow-5',
    'effects' => array(
      16 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '582',
          'height' => '269',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: seven-slideshow-6.
  $styles['seven-slideshow-6'] = array(
    'name' => 'seven-slideshow-6',
    'effects' => array(
      17 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '939',
          'height' => '370',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: seven-slideshow-7.
  $styles['seven-slideshow-7'] = array(
    'name' => 'seven-slideshow-7',
    'effects' => array(
      19 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '396',
          'height' => '269',
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function core_ef_node_info() {
  $items = array(
    'data_company' => array(
      'name' => t('Company Application'),
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
