<?php

/**
 * @file
 * template.php
 */

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

//adding class to assessment menu
function bootstrap_menu_tree__menu_assessment(&$variables) {
  return '<ul class="menu nav nav-tabs">' . $variables['tree'] . '</ul>';
}

//adding class to borrowing menu
function bootstrap_menu_tree__menu_borrowing_menu(&$variables) {
  return '<ul class="menu nav nav-tabs">' . $variables['tree'] . '</ul>';
}

//adding class to library instruction menu
function bootstrap_menu_tree__menu_library_instruction(&$variables) {
  return '<ul class="menu nav nav-tabs">' . $variables['tree'] . '</ul>';
}

//adding class to services for visitors menu
function bootstrap_menu_tree__menu_visitors(&$variables) {
  return '<ul class="menu nav nav-tabs">' . $variables['tree'] . '</ul>';
}
//adding class to services for k12 menu
function bootstrap_menu_tree__menu_services_k12(&$variables) {
  return '<ul class="menu nav nav-tabs">' . $variables['tree'] . '</ul>';
}
//adding class to services for faculty menu
function bootstrap_menu_tree__menu_services_faculty(&$variables) {
  return '<ul class="menu nav nav-tabs">' . $variables['tree'] . '</ul>';
}
//adding class to giving menu
function bootstrap_menu_tree__menu_giving(&$variables) {
  return '<ul class="menu nav nav-tabs">' . $variables['tree'] . '</ul>';
}

//adding class to reserves menu
function bootstrap_menu_tree__menu_reserves(&$variables) {
  return '<ul class="menu nav nav-tabs">' . $variables['tree'] . '</ul>';
}

//adding class to robots menu
function bootstrap_menu_tree__menu_robots(&$variables) {
  return '<ul class="menu nav nav-tabs">' . $variables['tree'] . '</ul>';
}
//adding class to GIS menu
function bootstrap_menu_tree__menu_gis(&$variables) {
  return '<ul class="menu nav nav-tabs">' . $variables['tree'] . '</ul>';
}

//adding class to Citing Sources menu
function bootstrap_menu_tree__menu_citing_sources(&$variables) {
  return '<ul class="menu nav nav-tabs">' . $variables['tree'] . '</ul>';
}

//adding class to Events Reservation menu
function bootstrap_menu_tree__menu_event_reservation(&$variables) {
  return '<ul class="menu nav nav-tabs">' . $variables['tree'] . '</ul>';
}

//adding class to friends (on production) menu
function bootstrap_menu_tree__menu_friends_library(&$variables) {
  return '<ul class="menu nav nav-tabs">' . $variables['tree'] . '</ul>';
}
//adding class to fiends (on test) menu
function bootstrap_menu_tree__menu_friends_of_the_library(&$variables) {
  return '<ul class="menu nav nav-tabs">' . $variables['tree'] . '</ul>';
}

//adds homepage javascript file for summon search boxes
function library_bootstrap_subtheme_preprocess_node(&$vars, $hook) {
	 if ($vars['node']->nid == 476) {
	 	$options = array(
    		'group' => JS_THEME,
  		);
  		drupal_add_js(drupal_get_path('theme', 'library_bootstrap_subtheme'). '/js/home.js', $options);
	 }
}

