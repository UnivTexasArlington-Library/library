<?php
/**
* @file
* This is drupal views plugin class file.
*
* We are extending drupal views functionality and going to create a new plugin
* to meet our functionality. Without create new plugin we cannot alter views
* results dynamically.
*/

class views_org_chart_style_plugin extends views_plugin_style {

  public function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);
  }

  /**
   * Defines options for the style plugin.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['columns'] = array('default' => array());
    $options['contains'] = array('default' => array());
    $options['uses_fields'] = array('default' => FALSE, 'bool' => TRUE);
    return $options;
  }

  /**
   * Renders the style plugin's options form.
   */
  public function options_form(&$form, &$form_state) {

    // Attach javascript.
    parent::options_form($form, $form_state);
    if ($this->uses_fields()) {
      $opt = array('' => t('- None -'));
      $field_labels = $this->display->handler->get_field_labels(TRUE);
      $opt += $field_labels;
    }
    $options['views_org_chart_parend_id'] = $opt;
    $options['views_org_chart_primary_key'] = $opt;
    if (count($options) > 1) {

      $form['views_org_chart_parend_id'] = array(
        '#title' => t('Views Org Chart Parent ID'),
        '#type' => 'select',
        '#description' => t('It should be unique among all nodes and try to use integer value for this e.g nid, pid, uid etc.'),
        '#options' => $opt,
        '#default_value' => $this->options['views_org_chart_parend_id'],
      );
      $form['views_org_chart_primary_key'] = array(
        '#title' => t('Views Org Chart Primary Key'),
        '#type' => 'select',
        '#description' => t('The ID of the parent node which use as relationship to make a hierarchy structure.'),
        '#options' => $opt,
        '#default_value' => $this->options['views_org_chart_primary_key'],
      );
      $form['views_org_chart_tool_tip'] = array(
        '#title' => t('Views Org Chart Tool-tip text'),
        '#type' => 'select',
        '#description' => t('Tool-tip text to show, when a user hovers over this node.'),
        '#options' => $opt,
        '#default_value' => $this->options['views_org_chart_tool_tip'],
      );
      $form['views_org_chart_allowcollapse'] = array(
        '#title' => t('Collapse a Node'),
        '#type' => 'checkbox',
        '#description' => t('Determines if double click will collapse a node.'),
        '#default_value' => $this->options['views_org_chart_allowcollapse'],
      );
      $form['views_org_chart_nodeclass'] = array(
        '#title' => t('Add Custom Node Class'),
        '#type' => 'textfield',
        '#description' => t('A class name to assign to node elements. Apply CSS to this class name to specify colors or styles for the chart elements default is "google-visualization-orgchart-node".'),
        '#default_value' => $this->options['views_org_chart_nodeclass'],
      );
      $form['views_org_chart_selectedNodeClass'] = array(
        '#title' => t('Selected Node Class'),
        '#type' => 'textfield',
        '#description' => t('A class name to assign to selected node elements. Apply CSS to this class name to specify colors or styles for selected chart elements default is "google-visualization-orgchart-nodesel".'),
        '#default_value' => $this->options['views_org_chart_selectedNodeClass'],
      );
      $form['views_org_chart_size'] = array(
        '#title' => t('Views Org Chart Parent ID'),
        '#type' => 'select',
        '#description' => t('Inner node font size default is medium.'),
        '#options' => array('small' => t('Small'), 'medium' => t('Medium'), 'large' => t('Large')),
        '#default_value' => !empty($this->options['views_org_chart_size']) ? $this->options['views_org_chart_size'] : 'medium',
      );
    }
  }

  /**
   * Normalize a list of columns based upon the fields that are
   * available. This compares the fields stored in the style handler
   * to the list of fields actually in the view, removing fields that
   * have been removed and adding new fields in their own column.
   *
   * - Each field must be in a column.
   * - Each column must be based upon a field, and that field
   *   is somewhere in the column.
   * - Any fields not currently represented must be added.
   * - Columns must be re-ordered to match the fields.
   *
   * @param $columns
   *   An array of all fields; the key is the id of the field and the
   *   value is the id of the column the field should be in.
   * @param $fields
   *   The fields to use for the columns. If not provided, they will
   *   be requested from the current display. The running render should
   *   send the fields through, as they may be different than what the
   *   display has listed due to access control or other changes.
   *
   * @return array
   *    An array of all the sanitized columns.
   */
  function sanitize_columns($columns, $fields = NULL) {
    $sanitized = array();
    if ($fields === NULL) {
      $fields = $this->display->handler->get_option('fields');
    }
    // Preconfigure the sanitized array so that the order is retained.
    foreach ($fields as $field => $info) {
      // Set to itself so that if it isn't touched, it gets column
      // status automatically.
      $sanitized[$field] = $field;
    }

    foreach ($columns as $field => $column) {
      // first, make sure the field still exists.
      if (!isset($sanitized[$field])) {
        continue;
      }

      // If the field is the column, mark it so, or the column
      // it's set to is a column, that's ok
      if ($field == $column || $columns[$column] == $column && !empty($sanitized[$column])) {
        $sanitized[$field] = $column;
      }
      // Since we set the field to itself initially, ignoring
      // the condition is ok; the field will get its column
      // status back.
    }

    return $sanitized;
  }

  public function field_format_form(&$form, &$form_state, $field) {
    //  parent::field_format_form($form, $form_state, $field);
  }

  public function field_format_submit(&$form, &$form_state, $field) {
    
  }

  public function build_data_table(array &$results) {
    
  }

}
