<?php

/**
 * @file
 * PDF row fields plugin provides the the fields plugin for unformatted style.
 */


/**
 * This class contains all the functionality of the field PDF style.
 */
class views_pdf_plugin_row_fields extends views_plugin_row {
  /**
   * Renders the rows.
   */
  function render($row) {
    // Due of limitations of field renderer, we invoke them
    // here and not in the field render function.
    foreach ($this->view->field as $id => $field) {
      if (empty($field->options['exclude'])) {
        if (isset($this->options['formats'][$id])) {
          $options = $this->options['formats'][$id];
        }
        else {
          $options = array();
        }
        switch ($this->display->display_options['style_plugin']) {
          case 'pdf_unformatted':
            // Register the row for header & footer on the current page before writing
            // each field. This is necessary in case the fields for one record span
            // multiple pages, or there is a page break. Otherwise there can be pages
            // with missing headers and footers.
            $this->view->pdf->setHeaderFooter($row, $this->options, $this->view);

            $this->view->pdf->drawContent($row, $options, $this->view, $id);

            break;
          case 'pdf_grid':
            $options['grid'] = $this->options['grid'];
            $this->view->pdf->drawContent($row, $options, $this->view, $id);
            $this->options['grid']['new_cell'] = FALSE;
            break;
        }
      }
    }

    // Reset the row page number.
    $this->view->pdf->resetRowPageNumber();

  }

  /**
   * Option definitions
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['formats'] = array('default' => array());
    return $options;
  }

  /**
   * Provide a form for setting options.
   */
  function options_form(&$form, &$form_state) {
    $options = $this->display->handler->get_field_labels();
    $fields = $this->display->handler->get_option('fields');

    // If the style is grid, not all options are available.
    $all_options = $this->display->display_options['style_plugin'] != 'pdf_grid';

    $fonts = array_merge(array('default' => t('-- Default --')), views_pdf_get_font_list());
    $font_styles = array(
      'b' => t('Bold'),
      'i' => t('Italic'),
      'u' => t('Underline'),
      'd' => t('Line through'),
      'o' => t('Overline')
    );

    $relativeElements = array(
      'page' => t('Page'),
      'header_footer' => t('In header / footer'),
      'last_position' => t('Last Writing Position'),
      'self' => t('Field: Self'),
    );
    if (!$all_options) {
      $relativeElements['page'] = t('Grid cell');
      unset($relativeElements['header_footer']);
    }

    $align = array(
      'L' => t('Left'),
      'C' => t('Center'),
      'R' => t('Right'),
      'J' => t('Justify'),
    );

    $hyphenate = array(
      'none' => t('None'),
      'auto' => t('Detect automatically'),
    );
    $hyphenate = array_merge($hyphenate, views_pdf_get_hyphenations());


    if (empty($this->options['inline'])) {
      $this->options['inline'] = array();
    }

    $form['formats']['heading'] = array(
      '#type' => 'markup',
      '#prefix' => '<h4>',
      '#markup' => t('Enter field-specific style and position settings below'),
      '#suffix' => '</h4>',
    );
    foreach ($options as $field => $option) {

      if (!empty($fields[$field]['exclude'])) {
        continue;
      }

      $form['formats'][$field] = array(
        '#type' => 'fieldset',
        '#title' => check_plain($option),
        '#collapsed' => TRUE,
        '#collapsible' => TRUE,
      );

      $form['formats'][$field]['position'] = array(
        '#type' => 'fieldset',
        '#title' => t('Position Settings'),
        '#collapsed' => TRUE,
        '#collapsible' => TRUE,
      );

      $form['formats'][$field]['position']['object'] = array(
        '#type' => 'select',
        '#title' => t('Position relative to'),
        '#required' => FALSE,
        '#options' => $relativeElements,
        '#default_value' => !empty($this->options['formats'][$field]['position']['object']) ?
          $this->options['formats'][$field]['position']['object'] : 'last_position',
      );

      $form['formats'][$field]['position']['corner'] = array(
        '#type' => 'radios',
        '#title' => t('Position relative to corner'),
        '#required' => FALSE,
        '#options' => array(
          'top_left' => t('Top Left'),
          'top_right' => t('Top Right'),
          'bottom_left' => t('Bottom Left'),
          'bottom_right' => t('Bottom Right'),
        ),
        '#default_value' => !empty($this->options['formats'][$field]['position']['corner']) ?
          $this->options['formats'][$field]['position']['corner'] : 'top_left',
      );

      $relativeElements['field_' . $field] = t('Field: !field', array('!field' => $option));


      $form['formats'][$field]['position']['x'] = array(
        '#type' => 'textfield',
        '#title' => t('Position X'),
        '#required' => FALSE,
        '#default_value' => !empty($this->options['formats'][$field]['position']['x']) ?
          $this->options['formats'][$field]['position']['x'] : '',
      );

      $form['formats'][$field]['position']['y'] = array(
        '#type' => 'textfield',
        '#title' => t('Position Y'),
        '#required' => FALSE,
        '#default_value' => !empty($this->options['formats'][$field]['position']['y']) ?
          $this->options['formats'][$field]['position']['y'] : '',
      );

      $form['formats'][$field]['position']['width'] = array(
        '#type' => 'textfield',
        '#title' => t('Width'),
        '#required' => FALSE,
        '#default_value' => !empty($this->options['formats'][$field]['position']['width']) ?
          $this->options['formats'][$field]['position']['width'] : '',
      );

      $form['formats'][$field]['position']['height'] = array(
        '#type' => 'textfield',
        '#title' => t('Height'),
        '#required' => FALSE,
        '#default_value' => !empty($this->options['formats'][$field]['position']['height']) ?
          $this->options['formats'][$field]['position']['height'] : '',
      );

      $form['formats'][$field]['text'] = array(
        '#type' => 'fieldset',
        '#title' => t('Text Settings'),
        '#collapsed' => TRUE,
        '#collapsible' => TRUE,
      );

      $form['formats'][$field]['text']['font_size'] = array(
        '#type' => 'textfield',
        '#title' => t('Font Size'),
        '#size' => 10,
        '#default_value' => isset($this->options['formats'][$field]['text']['font_size']) ?
          $this->options['formats'][$field]['text']['font_size'] : '',
      );
      $form['formats'][$field]['text']['font_family'] = array(
        '#type' => 'select',
        '#title' => t('Font Family'),
        '#required' => TRUE,
        '#options' => $fonts,
        '#size' => 5,
        '#default_value' => isset($this->options['formats'][$field]['text']['font_family']) ?
          $this->options['formats'][$field]['text']['font_family'] : 'default',
      );
      $form['formats'][$field]['text']['font_style'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Font Style'),
        '#options' => $font_styles,
        '#size' => 10,
        '#default_value' => !isset($this->options['formats'][$field]['text']['font_style']) ?
          $this->display->handler->get_option('default_font_style') :
          $this->options['formats'][$field]['text']['font_style'],
      );
      $form['formats'][$field]['text']['align'] = array(
        '#type' => 'radios',
        '#title' => t('Alignment'),
        '#options' => $align,
        '#default_value' => !isset($this->options['formats'][$field]['text']['align']) ?
          $this->display->handler->get_option('default_text_align') :
          $this->options['formats'][$field]['text']['align'],
      );
      $form['formats'][$field]['text']['hyphenate'] = array(
        '#type' => 'select',
        '#title' => t('Text Hyphenation'),
        '#options' => $hyphenate,
        '#description' => t('If you want to use hyphenation, then you need to download from <a href="@url">ctan.org</a> your needed pattern set. Then upload it to the dir "hyphenate_patterns" in the TCPDF lib directory. Perhaps you need to create the dir first. If you select the automated detection, then we try to get the language of the current node and select an appropriate hyphenation pattern.', array('@url' => 'http://www.ctan.org/tex-archive/language/hyph-utf8/tex/generic/hyph-utf8/patterns/tex')),
        '#default_value' => !isset($this->options['formats'][$field]['text']['hyphenate']) ?
          $this->display->handler->get_option('default_text_hyphenate') :
          $this->options['formats'][$field]['text']['hyphenate'],
      );
      $form['formats'][$field]['text']['color'] = array(
        '#type' => 'textfield',
        '#title' => t('Text Color'),
        '#description' => t('If a value is entered without a comma, it will be interpreted as a hexadecimal RGB color. Normal RGB can be used by separating the components by a comma. e.g 255,255,255 for white. A CMYK color can be entered in the same way as RGB. e.g. 0,100,0,0 for magenta.'),
        '#size' => 20,
        '#default_value' => !isset($this->options['formats'][$field]['text']['color']) ?
          $this->display->handler->get_option('default_text_color') :
          $this->options['formats'][$field]['text']['color'],
      );
      $form['formats'][$field]['render'] = array(
        '#type' => 'fieldset',
        '#title' => t('Render Settings'),
        '#collapsed' => TRUE,
        '#collapsible' => TRUE,
      );

      if ($all_options) {
        $form['formats'][$field]['render']['is_html'] = array(
          '#type' => 'checkbox',
          '#title' => t('Render As HTML'),
          '#default_value' => isset($this->options['formats'][$field]['render']['is_html']) ?
            $this->options['formats'][$field]['render']['is_html'] : 1,
        );
        $form['formats'][$field]['render']['minimal_space'] = array(
          '#type' => 'textfield',
          '#title' => t('Minimal Space'),
          '#description' => t('Specify here the minimal space, which is needed on the page, that the content is placed on the page.'),
          '#default_value' => isset($this->options['formats'][$field]['render']['minimal_space']) ?
            $this->options['formats'][$field]['render']['minimal_space'] : 1,
        );
      }

      $form['formats'][$field]['render']['custom_layout'] = array(
        '#type' => 'checkbox',
        '#title' => t('Enable custom layout hook.'),
        '#description' => t("Allow a custom module to alter the layout of this field using hook_views_pdf_custom_layout()."),
        '#default_value' => !empty($this->options['formats'][$field]['render']['custom_layout']) ?
          $this->options['formats'][$field]['render']['custom_layout'] : FALSE,
      );
      $form['formats'][$field]['render']['custom_post'] = array(
        '#type' => 'checkbox',
        '#title' => t('Enable custom post render hook.'),
        '#description' => t("Allow a custom module to execute after the rendering of this field using hook_views_pdf_custom_post()."),
        '#default_value' => !empty($this->options['formats'][$field]['render']['custom_post']) ?
          $this->options['formats'][$field]['render']['custom_post'] : FALSE,
      );
      if (user_access('use PHP for settings') && VIEWS_PDF_PHP) {
        $form['formats'][$field]['render']['use_php'] = array(
          '#type' => 'checkbox',
          '#title' => t('Enable direct PHP code.'),
          '#description' => t("Show input boxes for direct PHP code (not recommended)."),
          '#default_value' => !empty($this->options['formats'][$field]['render']['use_php']) ?
            $this->options['formats'][$field]['render']['use_php'] :
            !empty($this->options['formats'][$field]['render']['eval_before']) ||
              !empty($this->options['formats'][$field]['render']['eval_after']),
        );
        $form['formats'][$field]['render']['eval_before'] = array(
          '#type' => 'textarea',
          '#title' => t('PHP Code Before Output'),
          '#description' =>
          t('Please avoid direct PHP here, this feature is deprecated in favour of the custom layout hook'),
          '#default_value' => isset($this->options['formats'][$field]['render']['eval_before']) ?
            $this->options['formats'][$field]['render']['eval_before'] : '',
          '#states' => array(
            'visible' => array(
              ":input[name=\"row_options[formats][$field][render][use_php]\"]" => array('checked' => TRUE),
            ),
          ),
        );
        $form['formats'][$field]['render']['bypass_eval_before'] = array(
          '#type' => 'checkbox',
          '#title' => t('Use the PHP eval function instead php_eval.'),
          '#description' => t("WARNING: If you don't know the risk of using eval leave unckecked."),
          '#default_value' => !empty($this->options['formats'][$field]['render']['bypass_eval_before']) ?
            $this->options['formats'][$field]['render']['bypass_eval_before'] : FALSE,
          '#states' => array(
            'visible' => array(
              ":input[name=\"row_options[formats][$field][render][use_php]\"]" => array('checked' => TRUE),
            ),
          ),
        );

        $form['formats'][$field]['render']['eval_after'] = array(
          '#type' => 'textarea',
          '#title' => t('PHP Code After Output'),
          '#description' =>
          t('Please avoid direct PHP here, this feature is deprecated in favour of the custom post render hook'),
          '#default_value' => isset($this->options['formats'][$field]['render']['eval_after']) ?
            $this->options['formats'][$field]['render']['eval_after'] : '',
          '#states' => array(
            'visible' => array(
              ":input[name=\"row_options[formats][$field][render][use_php]\"]" => array('checked' => TRUE),
            ),
          ),
        );
        $form['formats'][$field]['render']['bypass_eval_after'] = array(
          '#type' => 'checkbox',
          '#title' => t('Use the PHP eval function instead php_eval.'),
          '#description' => t("WARNING: If you don't know the risk of using eval leave unckecked."),
          '#default_value' => !empty($this->options['formats'][$field]['render']['bypass_eval_after']) ?
            $this->options['formats'][$field]['render']['bypass_eval_after'] : FALSE,
          '#states' => array(
            'visible' => array(
              ":input[name=\"row_options[formats][$field][render][use_php]\"]" => array('checked' => TRUE),
            ),
          ),
        );
      }
    }
  }

  /**
   * Stores the options
   */
  function options_submit(&$form, &$form_state) {
    $default = $this->display->handler->get_option('default_font_style');
    foreach ($form_state['values']['row_options']['formats'] as $id => &$field) {

      // Reset to default, if the elements are equal to the default settings
      if (count(array_diff($default, $field['text']['font_style'])) == 0 &&
          count(array_diff($field['text']['font_style'], $default)) == 0) {
        $field['text']['font_style'] = NULL;
      }

      if ($field['text']['align'] == $this->display->handler->get_option('default_text_align')) {
        $field['text']['align'] = NULL;
      }

      if ($field['text']['hyphenate'] == $this->display->handler->get_option('default_text_hyphenate')) {
        $field['text']['hyphenate'] = NULL;
      }

      // Check unset values (grid mode), and set defaults.
      if (!isset($field['render']['is_html'])) {
        $field['render']['is_html'] = 0;
      }

      // If use-PHP unchecked, clear PHP options.
      if (!$field['render']['use_php']) {
        $field['render']['eval_before'] = $field['render']['eval_after'] = '';
        $field['render']['bypass_eval_before'] = $field['render']['bypass_eval_after'] = FALSE;
      }
    }
  }
}
