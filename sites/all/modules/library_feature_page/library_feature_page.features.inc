<?php
/**
 * @file
 * library_feature_page.features.inc
 */

/**
 * Implements hook_node_info().
 */
function library_feature_page_node_info() {
  $items = array(
    'basic_page2' => array(
      'name' => t('Feature Page'),
      'base' => 'node_content',
      'description' => t('Paragraphs version of Basic Page'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
