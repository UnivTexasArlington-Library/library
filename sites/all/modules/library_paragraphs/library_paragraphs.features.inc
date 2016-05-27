<?php
/**
 * @file
 * library_paragraphs.features.inc
 */

/**
 * Implements hook_paragraphs_info().
 */
function library_paragraphs_paragraphs_info() {
  $items = array(
    'column2' => array(
      'name' => 'Column2',
      'bundle' => 'column2',
      'locked' => '1',
    ),
    'google_calendar' => array(
      'name' => 'Google Calendar',
      'bundle' => 'google_calendar',
      'locked' => '1',
    ),
    'test' => array(
      'name' => 'Text',
      'bundle' => 'test',
      'locked' => '1',
    ),
    'thumbnail_description' => array(
      'name' => 'Thumbnail Description',
      'bundle' => 'thumbnail_description',
      'locked' => '1',
    ),
  );
  return $items;
}
