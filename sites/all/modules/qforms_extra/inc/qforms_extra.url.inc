<?php

/**
 * @file
 * Qforms extra url element definition.
 */

function qforms_extra_fapi_url($element, array $params = array()) {
  $felement = qforms_fapi_text_element($element, $params);
  if (!isset($felement['#default_value'])) {
    $felement['#default_value'] = 'http://';
  }
  $felement['#element_validate'] = array('qforms_extra_fapi_url_validate');

  return $felement;
}

function qforms_extra_fapi_url_validate($element, &$form_state) {
  // Skip validation if field isn't required and if it is empty.
  if ($element['#required'] == FALSE && empty($element['#value'])) {
    return;
  }

  if (!valid_url($element['#value'], TRUE)) {
    form_error($element, t('You need to enter a valid url.'));
  }
}

function qforms_extra_element_url($element_data) {
  $element_data['element_title'] = t('Url');
  $element = qforms_element_default($element_data);
  qforms_element_add_size($element_data, $element);
  return $element;
}
