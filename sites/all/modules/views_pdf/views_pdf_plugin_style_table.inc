<?php

/**
 * @file
 * Table PDF style plugin
 */


/**
 * Style plugin to render each item as a row in a table.
 *
 * @ingroup views_style_plugins
 */
class views_pdf_plugin_style_table extends views_plugin_style {

  /**
   * Render the style
   */
  function render() {
    $this->view->numberOfRecords = count($this->view->result);
    $this->view->pdf->drawTable($this->view, $this->options);
  }


  /**
   * Option definitions
   */
  function option_definition() {
    $options = parent::option_definition();

    // Grouping not supported.
    $this->definition['uses grouping'] = FALSE;

    $options['info'] = array('default' => array());
    $options['position'] = array('default' => array());

    return $options;
  }

  /**
   * Options form
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $handlers = $this->display->handler->get_handlers('field');
    if (empty($handlers)) {
      $form['error_markup'] = array(
        '#markup' => '<div class="error messages">' . t('You need at least one field before you can configure your table settings') . '</div>',
      );
      return;
    }
    $attached = array(
      'css' => array(drupal_get_path('module', 'views_pdf') . '/theme/admin.css'),
    );

    $form['#theme'] = 'views_pdf_plugin_style_table';
    $form['#attached'] = $attached;

    $columns = array('_default_' => '');
    $columns += $this->display->handler->get_field_labels();
    $fields = $this->display->handler->get_option('fields');

    $fonts = array_merge(array('default' => t('-- Default --')), views_pdf_get_font_list());

    $font_styles = array(
      'b' => t('Bold'),
      'i' => t('Italic'),
      'u' => t('Underline'),
      'd' => t('Line through'),
      'o' => t('Overline')
    );
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

    foreach ($columns as $field => $column) {

      // Skip excluded fields and the page-break field.
      if (!empty($fields[$field]['exclude']) || $field == 'page_break') {
        continue;
      }

      $safe = str_replace(array('][', '_', ' '), '-', $field);

      // the $id of the column for dependency checking.
      $id = 'edit-style-options-columns-' . $safe;

      // markup for the field name
      $form['info'][$field]['name'] = array(
        '#markup' => $column,
      );

      foreach(array('header_style', 'body_style') as $style) {

        $info_text = empty($this->options['info'][$field][$style]['text']) ?
          NULL : $this->options['info'][$field][$style]['text'];

        $form['info'][$field][$style]['text'] = array(
          '#type' => 'fieldset',
          '#title' => t('Text Settings'),
          '#collapsed' => TRUE,
          '#collapsible' => TRUE,
        );

        $form['info'][$field][$style]['text']['font_size'] = array(
          '#type' => 'textfield',
          '#size' => 10,
          '#title' => t('Font Size'),
          '#default_value' => empty($info_text['font_size']) ? '' : $info_text['font_size'],
        );

        $form['info'][$field][$style]['text']['font_family'] = array(
          '#type' => 'select',
          '#title' => t('Font Family'),
          '#required' => TRUE,
          '#options' => $fonts,
          '#size' => 5,
          '#default_value' => empty($info_text['font_family']) ? 'default' : $info_text['font_family'],
        );

        $form['info'][$field][$style]['text']['font_style'] = array(
          '#type' => 'checkboxes',
          '#title' => t('Font Style'),
          '#options' => $font_styles,
          '#size' => 10,
          '#default_value' => empty($info_text['font_style']) ?
            $this->display->handler->get_option('default_font_style') : $info_text['font_style'],
        );
        $form['info'][$field][$style]['text']['align'] = array(
          '#type' => 'radios',
          '#title' => t('Alignment'),
          '#options' => $align,
          '#default_value' => empty($info_text['align']) ?
            $this->display->handler->get_option('default_text_align') : $info_text['align'],
        );

        $form['info'][$field][$style]['text']['hyphenate'] = array(
          '#type' => 'select',
          '#title' => t('Text Hyphenation'),
          '#options' => $hyphenate,
          '#description' => t('upload patterns from <a href="@url">ctan.org</a> to <br />sites/libraries/tcpdf/hyphenate_patterns', array('@url' => 'http://www.ctan.org/tex-archive/language/hyph-utf8/tex/generic/hyph-utf8/patterns/tex')),
          '#default_value' => empty($info_text['hyphenate']) ?
            $this->display->handler->get_option('default_text_hyphenate') : $info_text['hyphenate'],
        );

        $form['info'][$field][$style]['text']['color'] = array(
          '#type' => 'textfield',
          '#title' => t('Text Color'),
          '#description' => t('Enter Any format: <br />000000 (HexRGB) - 000,000,000 (RGB) - 000,000,000,000 (CMYK)'),
          '#size' => 10,
          '#default_value' => empty($info_text['color']) ?
            $this->display->handler->get_option('default_text_color') : $info_text['color'],
        );

        $form['info'][$field][$style]['text']['vpad'] = array(
          '#type' => 'textfield',
          '#title' => t('Vertical padding'),
          '#description' => t('Padding space to apply above and below text in each row (within borders if used)'),
          '#size' => 6,
          '#default_value' => empty($info_text['vpad']) ? '' : $info_text['vpad'],
        );

        $form['info'][$field][$style]['text']['border'] = array(
          '#type' => 'textfield',
          '#title' => t('Border'),
          '#description' => t('1 = full border, or any combination of letters L, R, T, B'),
          '#size' => 6,
          '#default_value' => empty($info_text['border']) ? '' : $info_text['border'],
        );

        if ($field != '_default_' && user_access('use PHP for settings') && VIEWS_PDF_PHP) {

          $info_render = empty($this->options['info'][$field][$style]['render']) ?
            NULL : $this->options['info'][$field][$style]['render'];

            $form['info'][$field][$style]['render'] = array(
            '#type' => 'fieldset',
            '#title' => t('Render Settings'),
            '#collapsed' => TRUE,
            '#collapsible' => TRUE,
          );
          $form['info'][$field][$style]['render']['eval_before'] = array(
            '#type' => 'textarea',
            '#title' => t('PHP Code Before Output'),
            '#description' =>
            t('Please avoid direct PHP here, this feature is deprecated in favour of hook_views_pdf_custom_layout()'),
            '#default_value' => empty($info_render['eval_before']) ? '' : $info_render['eval_before'],
          );
          $form['info'][$field][$style]['render']['bypass_eval_before'] = array(
            '#type' => 'checkbox',
            '#title' => t('Use the PHP eval function instead php_eval.'),
            '#description' => t("WARNING: If you don't know the risk of using eval leave unckecked."),
            '#default_value' => empty($info_render['bypass_eval_before']) ? FALSE : $info_render['bypass_eval_before'],
          );

          $form['info'][$field][$style]['render']['eval_after'] = array(
            '#type' => 'textarea',
            '#title' => t('PHP Code After Output'),
            '#description' =>
            t('Please avoid direct PHP here, this feature is deprecated in favour of hook_views_pdf_custom_post()'),
            '#default_value' => empty($info_render['eval_after']) ? '' : $info_render['eval_after'],
          );
          $form['info'][$field][$style]['render']['bypass_eval_after'] = array(
            '#type' => 'checkbox',
            '#title' => t('Use the PHP eval function instead php_eval.'),
            '#description' => t("WARNING: If you don't know the risk of using eval leave unckecked."),
            '#default_value' => empty($info_render['bypass_eval_after']) ? FALSE : $info_render['bypass_eval_after'],
          );
        }
      }

      if ($field != '_default_') {
        $form['info'][$field]['position']['width'] = array(
          '#type' => 'textfield',
          '#size' => 10,
          '#default_value' => isset($this->options['info'][$field]['position']['width']) ? $this->options['info'][$field]['position']['width'] : '',
        );

        $form['info'][$field]['empty']['hide_empty'] = array(
          '#type' => 'checkbox',
          '#default_value' => isset($this->options['info'][$field]['empty']['hide_empty']) ? $this->options['info'][$field]['empty']['hide_empty'] : 'FALSE',
        );
      }
    }

    // Some general options
    $form['position'] = array(
      '#type' => 'fieldset',
      '#title' => t('Layout'),
      '#collapsed' => FALSE,
      '#collapsible' => TRUE,
    );
    $form['position']['use_header'] = array(
      '#type' => 'checkbox',
      '#title' => t('Include column headings'),
      '#default_value' => isset($this->options['position']['use_header']) ? $this->options['position']['use_header'] : 1,
    );
    $form['position']['h'] = array(
      '#type' => 'textfield',
      '#size' => 10,
      '#title' => t('Header spacing'),
      '#description' => t('Vertical space between column headings and table data'),
      '#default_value' => isset($this->options['position']['h']) ? $this->options['position']['h'] : '',
      '#states' => array(
        'invisible' => array(
          ':input[name="style_options[position][use_header]"]' => array('checked' => FALSE),
        ),
      ),
    );
    $form['position']['row_height'] = array(
      '#type' => 'textfield',
      '#size' => 10,
      '#title' => t('Row Height'),
      '#description' => t('Height will always be enough for one line of text. A larger value will create space, and/or allow for multiple lines'),
      '#default_value' => isset($this->options['position']['row_height']) ? $this->options['position']['row_height'] : '',
    );
  }

  /**
   * Options form storage
   */
  function options_submit(&$form, &$form_state) {
    $default_font_style = $this->display->handler->get_option('default_font_style');

    foreach ($form_state['values']['style_options']['info'] as $id => $field) {
        foreach(array('header_style', 'body_style') as $style) {
          // Reset to default, if the elements are equal to the default settings.
          if (count(array_diff($default_font_style, $field[$style]['text']['font_style'])) == 0 &&
              count(array_diff($field[$style]['text']['font_style'], $default_font_style)) == 0) {
            $form_state['values']['style_options']['info'][$id][$style]['text']['font_style'] = NULL;
          }
          if ($field[$style]['text']['font_family'] == 'default') {
            $form_state['values']['style_options']['info'][$id][$style]['text']['font_family'] = NULL;
          }

          if ($field[$style]['text']['align'] == $this->display->handler->get_option('default_text_align')) {
            $form_state['values']['style_options']['info'][$id][$style]['text']['align'] = NULL;
          }

          if ($field[$style]['text']['hyphenate'] == $this->display->handler->get_option('default_text_hyphenate')) {
            $form_state['values']['style_options']['info'][$id][$style]['text']['hyphenate'] = NULL;
          }

          // Strip all empty values.
          $form_state['values']['style_options']['info'][$id][$style] =
            _array_filter_recursive($form_state['values']['style_options']['info'][$id][$style]);
      }
    }
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

/**
 * A recursive version of PHP array_filter().
 */
function _array_filter_recursive($input)
{
  foreach ($input as &$value) {
    if (is_array($value)) {
      $value = _array_filter_recursive($value);
    }
  }
  return array_filter($input);
}
