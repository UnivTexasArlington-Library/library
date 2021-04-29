<?php

/**
 * @file
 * Utils for Siteimprove Plugin.
 */

/**
 * Class SiteimproveUtils.
 */
class SiteimproveUtils {

  const TOKEN_REQUEST_URL = 'https://my2.siteimprove.com/auth/token';
  const JS_LIBRARY_URL = 'https://cdn.siteimprove.net/cms/overlay.js';

  /**
   * Return Siteimprove token.
   */
  public static function requestToken() {

    // Request new token.
    $headers = array('Accept' => 'application/json');
    $result = drupal_http_request(self::getTokenRequestUrl(), array('headers' => $headers));

    // If success, set token field with the new token.
    if ($result->code == 200) {
      $json = json_decode($result->data);
      if (!empty($json->token)) {
        return $json->token;
      }
    }

    watchdog('siteimprove', 'There was an error requesting a new token.', array(), WATCHDOG_ERROR);
    return FALSE;
  }

  /**
   * Prepare the token request URL.
   *
   * @return string
   *   The prepared token request URL.
   */
  public static function getTokenRequestUrl() {
    return self::TOKEN_REQUEST_URL . '?cms=Drupal-' . VERSION;
  }

  /**
   * Include all Siteimprove js scripts.
   *
   * @param string $url
   *   Url.
   * @param string $type
   *   Action: recheck|input|recrawl|domain.
   * @param bool $auto
   *   Automatic calling to the defined method.
   */
  public static function includeJs($url, $type, $auto = TRUE) {
    // Add Siteimprove JS.
    drupal_add_js(self::JS_LIBRARY_URL, 'external');
    // Add url and token to the JS settings.
    drupal_add_js(array(
      'siteimprove' => array(
        $type => array(
          'auto' => $auto,
          'url' => SiteimproveUtils::rewriteDomain($url),
        ),
        'token' => variable_get('siteimprove_token'),
      ),
    ), 'setting');
    // Include custom JS.
    drupal_add_js(drupal_get_path('module', 'siteimprove') . '/js/siteimprove.js');
  }

  /**
   * Save URL in session.
   *
   * @param object $entity
   *   Node or taxonomy term entity object.
   * @param string $id
   *   Name of identifier field:
   *     - nid: Node id.
   *     - tid: Taxonomy term id.
   * @param string $path
   *   Internal path of entity:
   *     - node/: Node path.
   *     - taxonomy/term/: Taxonomy term path.
   */
  public static function setSessionUrl($entity, $id, $path) {
    // Check if user has access.
    if (user_access(SITEIMPROVE_PERMISSION_USE)) {
      // Get friendly url of node and save in SESSION.
      $url = url($path . $entity->{$id}, array('absolute' => TRUE));
      $url = SiteimproveUtils::rewriteDomain($url);
      $_SESSION['siteimprove_url'][] = $url;
    }
  }

  /**
   * Rewrite domain in a URL.
   *
   * @param string $url
   *   The full URL to a page.
   */
  public static function rewriteDomain($url) {
    $frontend_domain = variable_get('siteimprove_frontend_domain');
    $rewritten_url = $url;

    // Rewrite domain.
    if (!empty($frontend_domain)) {
      $url_parts = parse_url($url);

      // Search string.
      $search = $url_parts['scheme'] .'://' . $url_parts['host'];
      $search = !empty($url_parts['port']) ? $search .':' . $url_parts['port'] : $search;

      // Replace string.
      $replace = $url_parts['scheme'] .'://' . $frontend_domain;

      // URL with rewritten domain.
      $rewritten_url = str_replace($search, $replace, $url);
    }

    // Let other modules alter the rewritten URL.
    $original_url = $url;
    drupal_alter('siteimprove_frontend_url', $rewritten_url, $original_url);

    return $rewritten_url;
  }

}
