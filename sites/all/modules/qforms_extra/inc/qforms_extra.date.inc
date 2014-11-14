<?php

/**
 * @file
 * Qforms extra date element definition.
 */

define('DEFAULT_DATE_FORMAT', 'm/d/Y');

/**
 * Returns date textfield with added jquery UI Date picker.
 */
function qforms_extra_fapi_date($element, array $params = array()) {
  $felement = qforms_fapi_text_element($element, $params);
  $felement['#element_validate'] = array('qforms_extra_fapi_date_validate');

  // Add jquery UI datepicker.
  drupal_add_library('system', 'ui.datepicker');

  $php_to_jquery_date_formats = array(
    'd' => 'dd',
    'j' => 'd',
    'l' => 'DD',
    'z' => 'o',
    'F' => 'MM',
    'm' => 'mm',
    'n' => 'm',
    'Y' => 'yy',
  );
  $jquery_date_format = ''; 
  $date_format = _qforms_extra_get_date_format($element);
  foreach (str_split($date_format) as $char_in_format) {
    $jquery_date_format .= isset($php_to_jquery_date_formats[$char_in_format]) ? $php_to_jquery_date_formats[$char_in_format] : $char_in_format;
  }

  if (!isset($felement['#attributes']) || $felement['#attributes']['readonly'] != 'readonly') {
    drupal_add_js('jQuery(document).ready(function() {
      jQuery( \'input[name="' . $element['key'] . '"]\' ).datepicker({ dateFormat: "' . $jquery_date_format . '" });
      });', 'inline');
  }
  return $felement;
}

/**
 * Validation of date textfield.
 */
function qforms_extra_fapi_date_validate($element, &$form_state) {
  // Skip validation if field isn't required and if it is empty.
  if ($element['#required'] == FALSE && empty($element['#value'])) {
    return;
  }
  // @Note - DateTime::createFromFormat() is introduced in PHP 5.3.0.
  foreach ($form_state['build_info']['args'] as $value) {
    if (is_array($value)) {
      if (isset($value[$element['#name']])) {
        $format = _qforms_extra_get_date_format($value[$element['#name']]);
      }
    }
  }
  $date = DateTime::createFromFormat(isset($format) ? $format : DEFAULT_DATE_FORMAT, $element['#value']);
  if (!$date) {
    form_error($element, t('You need to enter a valid date.'));
  }
}

/**
 * Returns qforms date element for form builder.
 */
function qforms_extra_element_date($element_data) {
  $element_data['element_title'] = t('Date');
  $element = qforms_element_default($element_data);

  qforms_element_add_size($element_data, $element);  
  _qforms_element_add_date_format($element, $element_data);

  return $element;
}

/************************/
/*** Helper functions ***/
/************************/

/**
 * Adds control for selecting and custom date format defining.
 */
function _qforms_element_add_date_format(&$element, $element_data) {
  $default_value = isset($element_data['format']) ? check_plain($element_data['format']) : DEFAULT_DATE_FORMAT;
  $element[$element_data['id'] . '_data'][$element_data['id'] . '_format'] = array(
    '#type' => 'select',
    '#title' => t('Format'),
    '#default_value' => $default_value,
  );
  $system_date_formats = system_get_date_formats();
  foreach ($system_date_formats['short'] as $format => $value) {
    $format = substr($format, 0, 5);
    $element[$element_data['id'] . '_data'][$element_data['id'] . '_format']['#options'][$format] = date($format);
  }

  $element[$element_data['id'] . '_data'][$element_data['id'] . '_format']['#options']['custom_format'] = 'Your format';
  $element[$element_data['id'] . '_data'][$element_data['id'] . '_custom_format'] = array(
    '#type' => 'textfield',
    '#title' => t('Your format'),
    '#description' => t('A user-defined date format. See the <a href="http://php.net/manual/en/function.date.php">PHP manual</a> for available options.' .
      '<br>Note: Following formats are not supported: Day(N, S, w), Month(t), Year(L,o).'),
    '#default_value' => isset($element_data['custom_format']) ? $element_data['custom_format'] : DEFAULT_DATE_FORMAT,
    '#size' => 30,
    '#states' => array(
      'visible' => array(
        ':input[name="' . $element_data['id'] . '_format"]' => array('value' => 'custom_format'),
      )
    )
  );
}

function _qforms_extra_get_date_format($element) {
  return ($element['format'] == 'custom_format') ? check_plain($element['custom_format']) : $element['format'];
}
