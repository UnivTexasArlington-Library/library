<?php
/**
 * @file
 * Themes the Office hours formatter and widget.
 */

/**
 * Theme function for field formatter.
 */
function theme_office_hours_field_formatter_default($vars) {
  $days2show = $vars['days'];
  $days2calc = $vars['days2calc'];
  $daynames = $vars['daynames'];
  $settings = $vars['settings'];

  switch ($settings['hoursformat']) {
    case 2:
      // 24hr with leading zero.
      $timeformat = 'H:i';
      break;

    case 0:
      // 24hr without leading zero.
      $timeformat = 'G:i';
      break;

    case 1:
      // 12hr ampm without leading zero.
      $timeformat = 'g:i a';
      break;

    case 3:
      // 12hr format as a.m. - p.m. without leading zero.
      $timeformat = 'g:i a';
      break;
  }

  // Minimum width for day labels. Adjusted when adding new labels.
  $max_label_length = 3;

  $html_hours = '';
  $html_current_status = '';
  foreach ($days2show as $day => &$info) {
    // Format the label.
    $label = $daynames[$info['startday']];
    $label .= !isset($info['endday']) ? '' : $settings['separator_grouped_days'] . $daynames[$info['endday']];
    $label .= $settings['separator_day_hours'];
    $max_label_length = max($max_label_length, drupal_strlen($label));

    // Format the time.
    if (!$info['times']) {
      // Closed day.
      $times = t($settings['closedformat']);
      $comment = NULL;
    }
    else {
      $times = array();
      foreach ($info['times'] as $block_times) {
        $times[] = theme(
                    'office_hours_time_range',
                    array(
                      'times'       => $block_times,
                      'format'      => $timeformat,
                      'separator'   => $settings['separator_hours_hours'],
                      'comment'     => $block_times['comment'],
                    )
                  );
      }
      $times = implode($settings['separator_more_hours'], $times);
      if ($settings['hoursformat'] == 3) {
        $times = str_replace(array('am','pm'), array('a.m.','p.m.'), $times);
      }
    }

    $info['output_label'] = $label;
    $info['output_times'] = $times;
  }

  // Start the loop again - only now we have the correct $max_label_length.
  foreach ($days2show as $day => &$info) {
    // Remove unwanted lines.
    switch ($settings['showclosed']) {
      case 'all':
        break;

      case 'open':
        if (!isset($info['times'])) {
          continue 2;
        }
        break;

      case 'next':
        if (!$info['current'] && !$info['next']) {
          continue 2;
        }
        break;

      case 'none':
        continue 2;
        break;
    }

    // Generate HTML for Hours.
    $html_hours .= '<span class="oh-display">'
               . '<span class="oh-display-label" style="width: ' . ($max_label_length * 0.60) . 'em;">'
               . filter_xss_admin($info['output_label'])
               . '</span>'
               . '<div span class="oh-display-times oh-display-' . (!$info['times'] ? 'closed' : 'hours')
               . ($info['current'] ? ' oh-display-current' : '')
               . '">'
               . filter_xss_admin($info['output_times'] . $settings['separator_days'])
               . '</div>'
               . '</span>';
  }

  $html = '<span class="oh-wrapper' . ($settings['grouped'] ? ' oh-display-grouped' : '') . '">' . $html_hours . '</span>';

  if ($settings['current_status']['position'] !== 'hide') {
    // Generate HTML for CurrentStatus. Visibility is switched in js, otherwise the output might be wrong with static caching.
    $context_id_array = entity_extract_ids($vars['context']['entity_type'], $vars['context']['entity']);
    $context_id = implode('-', $context_id_array);
    $html_current_status = '<div class="oh-current-wrapper" data-oh-current-context_id="' . $context_id . '">';
    $html_current_status .= '<div class="oh-current-open element-hidden">' . $settings['current_status']['open_text'] . '</div>';
    $html_current_status .= '<div class="oh-current-closed element-hidden">' . $settings['current_status']['closed_text'] . '</div>';
    $html_current_status .= '</div>';
    drupal_add_js(array(
      'office_hours' => array (
        'instances' => array (
          $context_id => array (
            'days2calc' => $days2calc,
          )
        )
      ),
    ), 'setting');

    switch ($settings['current_status']['position']) {
      case 'before':
        $html = $html_current_status . $html_hours;
        break;

      case 'after':
        $html = $html_hours . $html_current_status;
        break;
    }
  }

  return $html;
}

/**
 * Theme function for formatter: time ranges.
 */
function theme_office_hours_time_range($vars = array()) {
  // Add default values to $vars if not set already.
  $vars += array(
    'times' => array(
      'start' => '',
      'end' => '',
    ),
    'format' => 'G:i',
    'separator' => ' - ',
  );

  $starttime = _office_hours_time_format($vars['times']['start'], $vars['format']);
  $endtime = _office_hours_time_format($vars['times']['end'], $vars['format']);
  $comment = $vars['times']['comment'];
  if ($endtime == '0:00' || $endtime == '00:00') {
    $endtime = '24:00';
  }
  $result = $starttime . $vars['separator'] . $endtime . ' ' . $comment;
  return $result;
}

/**
 * Theme function for widget: office hours block.
 */
function theme_office_hours_block($vars) {
  return $vars['element']['#children'];
}

/**
 * Theme function for widget: office hours selector element.
 */
function theme_office_hours_select($vars) {
  return $vars['element']['#children'];
}

/**
 * Theme function for widget: office_hours complete week.
 */
function theme_office_hours_week($variables) {
  $element = $variables['element'];
  $output = '';
  $table_id = drupal_html_id($element['#field_name'] . '_values');
  $required = !empty($element['#required']) ? theme('form_required_marker', $variables) : '';

  $header = array(
    array(
      'data' => '<label>' . t('!title: !required', array('!title' => $element['#title'], '!required' => $required)) . "</label>",
      'class' => array('field-label'),
    ),
  );

  $rows = array();
  foreach (element_children($element) as $key) {
    $rows[] = array(
      drupal_render($element[$key]),
    );
  }

  $output = '<div class="form-item">';
  $output .= theme('table',
                   array(
                     'header' => $header,
                     'rows' => $rows,
                     'attributes' => array(
                       'id' => $table_id,
                       'class' => array('field-multiple-table'),
                     ),
                   )
                 );
  $output .= $element['#description'] ? '<div class="description">' . $element['#description'] . '</div>' : '';
  $output .= '</div>';

  return $output;
}
