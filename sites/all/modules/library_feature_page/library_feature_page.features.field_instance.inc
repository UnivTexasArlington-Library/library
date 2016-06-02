<?php
/**
 * @file
 * library_feature_page.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function library_feature_page_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-basic_page2-field_body2'.
  $field_instances['node-basic_page2-field_body2'] = array(
    'bundle' => 'basic_page2',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'paragraphs',
        'settings' => array(
          'view_mode' => 'full',
        ),
        'type' => 'paragraphs_view',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_body2',
    'label' => 'Body',
    'required' => 0,
    'settings' => array(
      'add_mode' => 'select',
      'allowed_bundles' => array(
        'column2' => 'column2',
        'google_calendar' => 'google_calendar',
        'test' => 'test',
        'thumbnail_description' => 'thumbnail_description',
        'top_image' => -1,
      ),
      'bundle_weights' => array(
        'column2' => 5,
        'google_calendar' => 8,
        'test' => 2,
        'thumbnail_description' => 3,
        'top_image' => -10,
      ),
      'default_edit_mode' => 'open',
      'description_display' => 'after',
      'title' => 'Paragraph',
      'title_multiple' => 'Paragraphs',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'paragraphs',
      'settings' => array(),
      'type' => 'paragraphs_embed',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-basic_page2-field_top_image'.
  $field_instances['node-basic_page2-field_top_image'] = array(
    'bundle' => 'basic_page2',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_top_image',
    'label' => 'Top Image',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'alt_field_required' => 1,
      'default_image' => 0,
      'description_display' => 'after',
      'file_directory' => 'images',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'title_field_required' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'media',
      'settings' => array(
        'allowed_schemes' => array(
          'public' => 'public',
        ),
        'allowed_types' => array(
          'audio' => 0,
          'default' => 0,
          'image' => 'image',
          'video' => 0,
        ),
        'progress_indicator' => 'throbber',
      ),
      'type' => 'media_generic',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Body');
  t('Top Image');

  return $field_instances;
}
