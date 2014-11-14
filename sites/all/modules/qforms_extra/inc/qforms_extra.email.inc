<?php

/**
 * @file
 * Qforms extra email element definition.
 */

function qforms_extra_fapi_email($element, array $params = array()) {
  $felement = qforms_fapi_text_element($element, $params);
  $felement['#element_validate'] = array('qforms_extra_fapi_email_validate');
  return $felement;
}

function qforms_extra_fapi_email_validate($element, &$form_state) {
  // Skip validation if field isn't required and if it is empty.
  if ($element['#required'] == FALSE && empty($element['#value'])) {
    return;
  }

  if (!valid_email_address($element['#value'])) {
    form_error($element, t('You need to enter a valid email address.'));
  }
}

function qforms_extra_element_email($element_data) {
  $element_data['element_title'] = t('Email');
  $element = qforms_element_default($element_data);
  qforms_element_add_size($element_data, $element);

  return $element;
}
