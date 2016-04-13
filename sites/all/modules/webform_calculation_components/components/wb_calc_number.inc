<?php
/**
 * @file
 * Webform module calculation number component.
 */

if (!defined('MAX_DECIMALS')) {
  define('MAX_DECIMALS', 31);
}

/**
 * Implements _webform_defaults_component().
 */
function _webform_defaults_wb_calc_number() {
  return array(
    'name' => '',
    'form_key' => NULL,
    'pid' => 0,
    'weight' => 0,
    'value' => '',
    'required' => 0,
    'extra' => array(
      'width' => '15',
      'maxlength' => '',
      'field_prefix' => '',
      'field_suffix' => '',
      'disabled' => 0,
      'unique' => 0,
      'title_display' => 0,
      'description' => '',
      'placeholder' => '',
      'attributes' => array(),
      'private' => FALSE,
      'analysis' => FALSE,
      'decimals' => 0,
      'operation_type' => '',
      'result_field' => '',
    ),
  );
}

/**
 * Implements _webform_theme_component().
 */
function _webform_theme_wb_calc_number() {
  return array(
    'webform_display_wb_calc_number' => array(
      'render element' => 'element',
  // 'file' => '/components/wb_calc_number.inc',
    ),
  );
}

/**
 * Implements _webform_edit_component().
 */
function _webform_edit_wb_calc_number($component) {
  $form = array();

  $webformnode = node_load($component['nid']);
  $available_numeric_fields = array();
  foreach ($webformnode->webform['components'] as $component_element) {
    if ($component_element['type'] == 'number' || $component_element['type'] == 'wb_calc_number') {
      $available_numeric_fields[$component_element['form_key']] = $component_element['name'];
    }
  }

  $form['value'] = array(
    '#type' => 'textfield',
    '#title' => t('Default value'),
    '#default_value' => $component['value'],
    '#description' => t('The default value of the webform calculation number field.') . ' ' . theme('webform_token_help'),
    '#size' => 60,
    '#maxlength' => 1024,
    '#weight' => 0,
  );
  $form['display']['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#default_value' => $component['extra']['width'],
    '#description' => t('Width of the webform calculation number field.') . ' ' . t('Leaving blank will use the default size.'),
    '#size' => 5,
    '#maxlength' => 10,
    '#weight' => 0,
    '#parents' => array('extra', 'width'),
  );
  $form['display']['placeholder'] = array(
    '#type' => 'textfield',
    '#title' => t('Placeholder'),
    '#default_value' => $component['extra']['placeholder'],
    '#description' => t('The placeholder will be shown in the field until the user starts entering a value.'),
    '#weight' => 1,
    '#parents' => array('extra', 'placeholder'),
  );
  $form['display']['field_prefix'] = array(
    '#type' => 'textfield',
    '#title' => t('Prefix text placed to the left of the webform calculation number field'),
    '#default_value' => $component['extra']['field_prefix'],
    '#description' => t('Examples: $, #, -.'),
    '#size' => 20,
    '#maxlength' => 127,
    '#weight' => 2.1,
    '#parents' => array('extra', 'field_prefix'),
  );
  $form['display']['field_suffix'] = array(
    '#type' => 'textfield',
    '#title' => t('Postfix text placed to the right of the webform calculation number field'),
    '#default_value' => $component['extra']['field_suffix'],
    '#description' => t('Examples: lb, kg, %.'),
    '#size' => 20,
    '#maxlength' => 127,
    '#weight' => 2.2,
    '#parents' => array('extra', 'field_suffix'),
  );
  $form['display']['disabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disabled'),
    '#return_value' => 1,
    '#description' => t('Make this field non-editable. Useful for setting an unchangeable default value.'),
    '#weight' => 11,
    '#default_value' => $component['extra']['disabled'],
    '#parents' => array('extra', 'disabled'),
  );
  $form['validation']['unique'] = array(
    '#type' => 'checkbox',
    '#title' => t('Unique'),
    '#return_value' => 1,
    '#description' => t('Check that all entered values for this field are unique. The same value is not allowed to be used twice.'),
    '#weight' => 1,
    '#default_value' => $component['extra']['unique'],
    '#parents' => array('extra', 'unique'),
  );
  $form['validation']['maxlength'] = array(
    '#type' => 'textfield',
    '#title' => t('Maxlength'),
    '#default_value' => $component['extra']['maxlength'],
    '#description' => t('Maximum length of the webform calculation number field value.'),
    '#size' => 5,
    '#maxlength' => 10,
    '#weight' => 2,
    '#parents' => array('extra', 'maxlength'),
  );
  $form['extra']['decimals'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of decimals'),
    '#default_value' => $component['extra']['decimals'],
    '#description' => t('Number of decimals of the calcaulation field. Minimun: 0 (integer), Maximum: @max_decimals.', array('@max_decimals' => MAX_DECIMALS)),
    '#size' => 5,
    '#maxlength' => 3,
    '#parents' => array('extra', 'decimals'),
    '#element_validate' => array('_webform_edit_decimals_validate'),
  );
  $form['extra']['operation_type'] = array(
    '#type' => 'select',
    '#title' => t('Operation'),
    '#default_value' => $component['extra']['operation_type'],
    '#options' => array(
      'addition' => t('Addition') . ' (+)',
      'subtraction' => t('Subtraction') . ' (-)',
      'multiplication' => t('Multiplication') . ' (*)',
      'division' => t('Division') . ' (/)',
      'percentage' => t('Percentage'),
      'modulo' => t('Modulo'),
    ),
    '#description' => t('E.g. Addition, Multiplication etc.'),
    '#parents' => array('extra', 'operation_type'),
  );
  $form['extra']['result_field'] = array(
    '#type' => 'select',
    '#default_value' => $component['extra']['result_field'],
    '#title' => t('Result field'),
    '#options' => $available_numeric_fields,
    '#description' => t('Select the numeric component as the result field or target of the operation.'),
    '#parents' => array('extra', 'result_field'),
  );

  return $form;
}

/**
 * Validation of decimals edit form items.
 */
function _webform_edit_decimals_validate($element, &$form_state) {
  if (!ctype_digit($element['#value'])) {
    form_error($element, t('Number of decimals has to contain only digits.'));
  }
  elseif ((int)$element['#value'] > MAX_DECIMALS) {
    form_error($element, t('Maximum number of decimals is @max.', array('@max' => MAX_DECIMALS)));
  }
  return TRUE;
}

/**
 * Implements _webform_render_component().
 */
function _webform_render_wb_calc_number($component, $value = NULL, $filter = TRUE) {
  $node = isset($component['nid']) ? node_load($component['nid']) : NULL;

  $element = array(
    '#type' => 'textfield',
    '#title' => $filter ? webform_filter_xss($component['name']) : $component['name'],
    '#title_display' => $component['extra']['title_display'] ? $component['extra']['title_display'] : 'before',
    '#default_value' => $filter ? webform_replace_tokens($component['value'], $node) : $component['value'],
    '#required' => $component['required'],
    '#weight' => $component['weight'],
    '#field_prefix' => empty($component['extra']['field_prefix']) ? NULL : ($filter ? webform_filter_xss($component['extra']['field_prefix']) : $component['extra']['field_prefix']),
    '#field_suffix' => empty($component['extra']['field_suffix']) ? NULL : ($filter ? webform_filter_xss($component['extra']['field_suffix']) : $component['extra']['field_suffix']),
    '#description' => $filter ? webform_filter_descriptions($component['extra']['description'], $node) : $component['extra']['description'],
    '#attributes' => $component['extra']['attributes'],
    '#theme_wrappers' => array('webform_element'),
    '#translatable' => array(
      'title',
      'description',
      'field_prefix',
      'field_suffix',
    ),
  );

  if ($component['extra']['placeholder']) {
    $element['#attributes']['placeholder'] = $component['extra']['placeholder'];
  }

  if ($component['extra']['disabled']) {
    if ($filter) {
      $element['#attributes']['readonly'] = 'readonly';
    }
    else {
      $element['#disabled'] = TRUE;
    }
  }

  // Enforce uniqueness.
  if ($component['extra']['unique']) {
    $element['#element_validate'][] = 'webform_validate_unique';
  }

  // Change the 'width' option to the correct 'size' option.
  if ($component['extra']['width'] > 0) {
    $element['#size'] = $component['extra']['width'];
  }
  if ($component['extra']['maxlength'] > 0) {
    $element['#maxlength'] = $component['extra']['maxlength'];
  }

  if (isset($value[0])) {
    $element['#default_value'] = $value[0];
  }

  if (($component['extra']['decimals'] > 0) && ($component['extra']['decimals'] < MAX_DECIMALS)) {
    $element['#element_validate'][] = '_webform_edit_validate_wb_calc_number';
  }
  if ($component['extra']['operation_type'] == 'value') {
    $element['#value'] = $element['#default_value'];
  }
  if ($component['extra']['result_field'] == 'value') {
    $element['#value'] = $element['#default_value'];
  }

  return $element;
}

/**
 * Element validation callback. Ensure keys are not duplicated.
 */
function _webform_edit_validate_wb_calc_number($element, &$form_state) {
  $error = FALSE;
  if (isset($element['#value'])) {
    if (isset($element['#webform_component']['extra']['decimals'])) {
      $decimals = $element['#webform_component']['extra']['decimals'];
    }
    else {
      $decimals = 0;
    }
    // Strip all non-numeric characters except -+., e.g. -12,000.4356
    $pattern = '@^[-+]?[0-9]*\.?[0-9]*$@';
    $times_of_matches = preg_match($pattern, $element['#value'], $matches);
    if ($times_of_matches == 0) {
      $error = TRUE;
    }
  }
  if ($error) {
    form_error($element, t('%value is not a valid webform calculation number.', array('%value' => trim($element['#value']))));
  }
  else {
    // Set the selected number of decimals of the webform calculation number.
    $wb_calc_number = round($matches[0], $decimals);
    $formatted_wb_calc_number = sprintf('%.0' . $decimals . 'f', $wb_calc_number);
    // Update the value of this element so the field can be validated.
    form_set_value($element, array($formatted_wb_calc_number), $form_state);
  }
}

/**
 * Implements _webform_display_component().
 */
function _webform_display_wb_calc_number($component, $value, $format = 'html') {
  return array(
    '#title' => $component['name'],
    '#weight' => $component['weight'],
    '#theme' => 'webform_display_wb_calc_number',
    '#theme_wrappers' => $format == 'html' ? array('webform_element') : array('webform_element_text'),
    '#field_prefix' => $component['extra']['field_prefix'],
    '#field_suffix' => $component['extra']['field_suffix'],
    '#format' => $format,
    '#value' => isset($value[0]) ? $value[0] : '',
    '#translatable' => array('title', 'field_prefix', 'field_suffix'),
  );
}

/**
 * Format the output of data for this component.
 */
function theme_webform_display_wb_calc_number($variables) {
  $element = $variables['element'];
  $prefix = $element['#format'] == 'html' ? '' : $element['#field_prefix'];
  $suffix = $element['#format'] == 'html' ? '' : $element['#field_suffix'];
  $value = $element['#format'] == 'html' ? check_plain($element['#value']) : $element['#value'];
  return $value !== '' ? ($prefix . $value . $suffix) : ' ';
}

/**
 * Implements _webform_analysis_component().
 */
function _webform_analysis_wb_calc_number($component, $sids = array()) {
  $query = db_select('webform_submitted_data', 'wsd', array('fetch' => PDO::FETCH_ASSOC))
    ->fields('wsd', array('data'))
    ->condition('nid', $component['nid'])
    ->condition('cid', $component['cid']);

  if (count($sids)) {
    $query->condition('sid', $sids, 'IN');
  }

  $nonblanks = 0;
  $submissions = 0;
  $wordcount = 0;

  $result = $query->execute();
  foreach ($result as $data) {
    if (drupal_strlen(trim($data['data'])) > 0) {
      $nonblanks++;
      $wordcount += str_word_count(trim($data['data']));
    }
    $submissions++;
  }

  $rows[0] = array(t('Left Blank'), ($submissions - $nonblanks));
  $rows[1] = array(t('User entered value'), $nonblanks);

  $other[] = array(
    t('Average submission length in words (ex blanks)'),
    ($nonblanks != 0 ? number_format($wordcount / $nonblanks, 2) : '0'));

  return array(
    'table_rows' => $rows,
    'other_data' => $other,
  );
}

/**
 * Implements _webform_table_component().
 */
function _webform_table_wb_calc_number($component, $value) {
  return check_plain(empty($value[0]) ? '' : $value[0]);
}

/**
 * Implements _webform_csv_headers_component().
 */
function _webform_csv_headers_wb_calc_number($component, $export_options) {
  $header = array();
  $header[0] = '';
  $header[1] = '';
  $header[2] = $export_options['header_keys'] ? $component['form_key'] : $component['name'];
  return $header;
}

/**
 * Implements _webform_csv_data_component().
 */
function _webform_csv_data_wb_calc_number($component, $export_options, $value) {
  return !isset($value[0]) ? '' : $value[0];
}
