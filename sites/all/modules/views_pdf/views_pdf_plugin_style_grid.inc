<?php


/**
 * @file
 * Grid PDF style
 */


/**
 * This class holds all the funtionality used for the grid style plugin.
 */
class views_pdf_plugin_style_grid extends views_plugin_style {

  /**
   * Render the style.
   *
   * @see views_pdf_views_plugins()
   */
  function render() {
    $options = $this->options['info'];

    $cols = $options['columns'];
    $colspace = $options['column_space'];
    $rows = $options['rows'];
    $rowspace = $options['row_space'];

    // Need to add the first page here to get dimensions.
    $this->view->pdf->addPage();
    $fullpage = FALSE;
    // Calculate grid parameters - cell size and offsets.
    $pgdim = $this->view->pdf->getPageDimensions();
    $cell_width = ($pgdim['wk'] - $pgdim['lm'] - $pgdim['rm'] - $colspace * ($cols - 1)) / $cols;
    $cell_height = ($pgdim['hk'] - $pgdim['tm'] - $pgdim['bm'] - $rowspace * ($rows - 1)) / $rows;

    $this->row_plugin->options['grid'] = array(
      'w' => $cell_width,
      'h' => $cell_height,
    );

    // Set up indirect variables so as to iterate row-wise or column-wise.
    if ($options['col_wise']) {
      $first = $rows;
      $second = $cols;
      $first_idx = 'rowidx';
      $second_idx = 'colidx';
    }
    else {
      $first = $cols;
      $second = $rows;
      $first_idx = 'colidx';
      $second_idx = 'rowidx';
    }

    $colidx = $rowidx = 0;
    $this->view->row_index = 0;
    foreach ($this->view->result as $row) {
      if ($fullpage) {
          $this->view->pdf->addPage();
          $fullpage = FALSE;
      }
      // Calculate co-ordinates of top left corner of current grid cell.
      $this->row_plugin->options['grid']['x'] = $colidx * ($cell_width + $colspace);
      $this->row_plugin->options['grid']['y'] = $rowidx * ($cell_height + $rowspace);
      $this->row_plugin->options['grid']['new_cell'] = TRUE;

      $this->row_plugin->render($row);
      $this->view->row_index++;

      // Use variable-variables to run row or column wise.
      if (++$$first_idx == $first) {
        $$first_idx = 0;
        if (++$$second_idx == $second) {
          $$second_idx = 0;
          $fullpage = TRUE;
        }
      }
    }
  }

  /**
   * Option definitions
   */
  function option_definition() {
    $options = parent::option_definition();

    // Grouping not supported.
    $this->definition['uses grouping'] = FALSE;

    $options['info'] = array(
      'columns' => 2,
      'column_space' => 0,
      'rows' => 8,
      'row_space' => 0,
      'col_wise' => 0,
    );

    return $options;
  }

  /**
   * Options form
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $attached = array(
      'css' => array(drupal_get_path('module', 'views_pdf') . '/theme/admin.css'),
    );
    $form['#attached'] = $attached;

    if (empty($this->options['info'])) {
      $this->options = $this->option_definition();
    }

    $form['info']['columns'] = array(
      '#type' => 'textfield',
      '#attributes' => array('type' => 'number', 'min' => 1),
      '#size' => 4,
      '#title' => t('Grid columns'),
      '#default_value' => $this->options['info']['columns'],
    );
    $form['info']['column_space'] = array(
      '#type' => 'textfield',
      '#attributes' => array('type' => 'number', 'min' => 0),
      '#size' => 4,
      '#title' => t('Column spacing'),
      '#default_value' => $this->options['info']['column_space'],
    );
    $form['info']['rows'] = array(
      '#type' => 'textfield',
      '#attributes' => array('type' => 'number', 'min' => 1),
      '#size' => 4,
      '#title' => t('Grid rows'),
      '#default_value' => $this->options['info']['rows'],
    );
    $form['info']['row_space'] = array(
      '#type' => 'textfield',
      '#attributes' => array('type' => 'number', 'min' => 0),
      '#size' => 4,
      '#title' => t('Row spacing'),
      '#default_value' => $this->options['info']['row_space'],
    );
    $form['info']['col_wise'] = array(
      '#type' => 'radios',
      '#title' => t('Layout order'),
      '#options' => array('Row-first', 'Column-first'),
      '#default_value' => $this->options['info']['col_wise'],
    );
  }

  /**
   * Attach this view to another display.
   */
  function attach_to($display_id, $path, $title) {
    $display = $this->view->display[$display_id]->handler;
    $url_options = array();
    $input = $this->view->get_exposed_input();
    if ($input) {
      $url_options['query'] = $input;
    }

    if (empty($this->view->feed_icon)) {
      $this->view->feed_icon = '';
    }
    $this->view->feed_icon .= theme(
      'views_pdf_icon',
      array(
        'path' => $this->view->get_url(NULL, $path),
        'title' => $title,
        'options' => $url_options
      )
    );
  }

}
