<?php

/**
 * @file
 * template.php
 */
/*function library_bootstrap_subtheme_preprocess_page(&$variables) {
  // Add information about the number of sidebars.
    $variables['content_column_class'] = ' class="col-sm-10"';
}*/

//this adds custom js
function library_bootstrap_subtheme_preprocess_html(&$variables) {
  $options = array(
    'group' => JS_THEME,
  );
  drupal_add_js(drupal_get_path('theme', 'library_bootstrap_subtheme'). '/js/scripts.js', $options);
}

//this adds classes to non-bootstrap views with the common vertical cells format - uses rowspan module
function library_bootstrap_subtheme_preprocess_views_view_rowspan(&$vars) {
  $vars['classes_array'][] = 'table table-striped';
}

//adding class to spco menu
function bootstrap_menu_tree__menu_spco_menu(&$variables) {
  return '<ul class="menu nav nav-tabs">' . $variables['tree'] . '</ul>';
}