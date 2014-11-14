<?php

/**
 * @file
 * Qforms extra markup element definition.
 */

function qforms_extra_fapi_markup($element, array $params = array()) {
  // @TODO - we should use some markup filter here.
  $felement['#markup'] = check_plain($element['markup']);
  return $felement;
}

function qforms_element_markup_prepare_for_csv_export(&$elements_data, $key) {
  $elements_data[$key] = NULL;
}

function qforms_extra_element_markup($element_data) {
  $element_data['element_title'] = t('Markup');
  $element = qforms_element_common($element_data);

  $element[$element_data['id'] . '_data'] += array(
    $element_data['id'] . '_markup' => array(
      '#type' => 'textarea',
      '#title' => t('Markup'),
      '#default_value' => isset($element_data['markup']) ? $element_data['markup'] : '', // @TODO - we need here better markup filter.
      '#required' => TRUE,
    ),
  );

  return $element;
}
