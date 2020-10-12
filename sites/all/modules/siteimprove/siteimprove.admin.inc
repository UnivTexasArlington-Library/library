<?php

/**
 * @file
 * Administrative page callbacks for the siteimprove module.
 */

/**
 * Implements hook_admin_settings() for module settings configuration.
 */
function siteimprove_admin_settings_form($form_state) {

  $form['token'] = array(
    '#title' => t('Token'),
    '#type' => 'fieldset',
  );
  $form['token']['siteimprove_token'] = array(
    '#default_value' => variable_get('siteimprove_token'),
    '#description' => t('Configure Siteimprove Plugin token.'),
    '#maxlength' => 50,
    '#prefix' => '<div id="token-wrapper">',
    '#required' => TRUE,
    '#size' => 50,
    '#suffix' => '</div>',
    '#title' => t('Token'),
    '#type' => 'textfield',
  );
  $form['token']['siteimprove_request_new_token'] = array(
    '#ajax' => array(
      'callback' => 'siteimprove_admin_settings_form_ajax_request_token',
      'wrapper' => 'token-wrapper',
    ),
    '#limit_validation_errors' => array(),
    '#type' => 'button',
    '#value' => t('Request new token'),
  );

  $form['frontend_domain'] = array(
    '#title' => t('Frontend domain'),
    '#description' => t('Are you using a separate edit or backend domain? Then insert your frontend domain below, and this domain will be used in the Siteimprove overlay.'),
    '#type' => 'fieldset',
  );
  $form['frontend_domain']['siteimprove_frontend_domain'] = array(
    '#default_value' => variable_get('siteimprove_frontend_domain'),
    '#description' => t('Input your domain name. If you leave out http:// or https://, the scheme will inherit the scheme of the web request.'),
    '#maxlength' => 50,
    '#required' => FALSE,
    '#size' => 50,
    '#title' => t('Domain'),
    '#type' => 'textfield',
  );

  $form['#validate'][] = 'siteimprove_admin_settings_form_validate';

  return system_settings_form($form);
}

/**
 * Extra validation of the settings form.
 */
function siteimprove_admin_settings_form_validate(&$form, &$form_state) {
  $domain = $form_state['values']['siteimprove_frontend_domain'];
  if (!empty($domain) && !preg_match('/^(https?:\/\/)?([a-zA-Z0-9][a-zA-Z0-9-_]*\.)*[a-zA-Z0-9]*[a-zA-Z0-9-_]*[[a-zA-Z0-9]+(:\d+)?$/', $domain)) {
    form_set_error('siteimprove_frontend_domain', t('Only use valid domain names in this field - no trailing slash, no trailing whitespace.'));
  }
}

/**
 * Ajax callback function for requesting a new Siteimprove token.
 *
 * @return array
 *   Renderable array (the box element)
 */
function siteimprove_admin_settings_form_ajax_request_token($form, $form_state) {

  // Request new token.
  if ($token = SiteimproveUtils::requestToken()) {
    $form['token']['siteimprove_token']['#value'] = $token;
  }
  else {
    form_set_error('siteimprove_token', t('There was an error requesting a new token. Please try again in a few minutes.'));
  }

  return $form['token']['siteimprove_token'];
}
