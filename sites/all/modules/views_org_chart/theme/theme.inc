<?php
/**
* @file
* The theme system, which controls the output of Drupal.
*
* Here we alter the results before to output into tpl file.
*/
function template_preprocess_views_org_chart(&$vars) {
  drupal_add_js('sites/all/libraries/google_api/google_chart_api.js');
  $view = $vars['view'];
  $result = $vars['result'] = $vars['rows'];
  $vars['rows'] = array();
  $vars['field_classes'] = array();
  $options = $view->style_plugin->options;
  $handler = $view->style_plugin;
  // These are optional configurations
  $optional = new stdClass();
  $optional->allowCollapse = 'false';
  $optional->nodeClass = 'google-visualization-orgchart-node';
  $optional->selectedNodeClass = 'google-visualization-orgchart-nodesel';
  $optional->size = 'medium';
  foreach (array(
'views_org_chart_allowcollapse' => 'allowCollapse',
 'views_org_chart_nodeclass' => 'nodeClass',
 'views_org_chart_selectedNodeClass' => 'selectedNodeClass',
 'views_org_chart_size' => 'size') as $key => $val) {

    if (isset($options[$key])) {
      $optional->{$val} = $options[$key];
    }
  }
  // optional configuration end
  $css_id = drupal_clean_css_identifier('views-org-chart-' . $view->name . '-' . $view->current_display);
  $fields = &$view->field;
  $columns = $handler->sanitize_columns($options['columns'], $fields);
  $renders = $handler->render_fields($result);

//   template_preprocess_views_view_table($vars);

  /*
   * we need array structure like this
   * array( 
   *   0 => array (
   *     0=>std Class {
   *         v => 'primary_key',
   *         f => 'output data'
   *       },
   *     1 => 'parent_key',
   *     2 => 'tooltip text'
   *   ),
   *   1 =>array (
   *   --
   *   --
   *   )
   * );
   */

  $mod_row = array();
  $parent_key = '';
  $tool_tip = '';
  foreach ($result as $num => $row) {
    $obj = new stdClass();
    foreach ($columns as $field => $column) {
      $vars['fields'][$field] = drupal_clean_css_identifier($field);
      // Add field classes
      $vars['field_classes'][$field][$num] = '';
      if ($fields[$field]->options['element_default_classes']) {
        $vars['field_classes'][$field][$num] = "views-field views-field-" . $vars['fields'][$field];
      }
      if ($classes = $fields[$field]->element_classes($num)) {
        if ($vars['field_classes'][$field][$num]) {
          $vars['field_classes'][$field][$num] .= ' ';
        }

        $vars['field_classes'][$field][$num] .= $classes;
      }
      $vars['field_attributes'][$field][$num] = array();
      //  Add primary key into array

      if ($options['views_org_chart_primary_key'] == $field) {
        $obj->v = $renders[$num][$field];
      }
      // Add parent key into array
      if (trim($options['views_org_chart_parend_id']) == trim($field)) {
        $parent_key = $renders[$num][$field];
      }
      if (trim($options['views_org_chart_tool_tip']) == trim($field)) {
        $tool_tip = $renders[$num][$field];
      }
      if (!empty($fields[$field]) && empty($fields[$field]->options['exclude'])) {
        $label = check_plain(!empty($fields[$field]) ? "<label  for=\"views-org-chart-field-lable\">" . $fields[$field]->label() . "</label >" : '');
        $field_output = html_entity_decode($label) . ' ' . $renders[$num][$field];
        $element_type = $fields[$field]->element_type(TRUE, TRUE);
        if ($element_type) {
          $field_output = '<' . $element_type . '>' . html_entity_decode($label) . ' ' . $field_output . '</' . $element_type . '>';
        }

        // Don't bother with separators and stuff if the field does not show up.
        if (empty($field_output) && !empty($vars['rows'][$num][$column])) {
          continue;
        }

        // Place the field into the column, along with an optional separator.
        if (!empty($vars['rows'][$num][$column])) {
          if (!empty($options['info'][$column]['separator'])) {
            $vars['rows'][$num][$column] .= filter_xss_admin($options['info'][$column]['separator']);
          }
        }
        else {
          $vars['rows'][$num][$column] = '';
        }

        $vars['rows'][$num][$column] .= $field_output;
      }
      $obj->f = theme('views_org_chart_items', array('data' => $vars['rows'][$num]));
      $mod_row[$num][0] = $obj;
      $mod_row[$num][1] = $parent_key;
      $mod_row[$num][2] = strip_tags($tool_tip);
    }
  }
  $vars['views_org_chart_row'] = $mod_row;
  $vars['views_org_chart_cssid'] = $css_id;
  if (empty($vars['view']->live_preview)) {
    drupal_add_js(array('views_org_chart' => array('optional' => drupal_json_encode($optional), 'cssID' => $css_id)), 'setting');
    drupal_add_js(drupal_get_path('module', 'views_org_chart') . '/js/views_org_chart.js');
  }
}

function theme_views_org_chart_items($data) {
  $output = "<div class='views-org-chart-container'>";
  foreach ($data['data'] as $key => $field) {
    $output .= "<div class='views-org-chart-field views-org-chart-field-no-" . $key . "'>" . $field . "</div>";
  }
  $output .= "</div>";
  return $output;
}
