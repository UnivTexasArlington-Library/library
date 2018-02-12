<?php

/**
 * Implements hook_field_info().
 */
function blockreference_field_info() {
  return [
    'blockreference' => [
      'label' => t('Block reference'),
      'property_type' => 'block_moddelta',
      'property_callbacks' => ['blockreference_field_entity_property_callback'],
      'description' => t('This field stores the ID of a related block as an integer value.'),
      'settings' => [
        'referenceable_modules' => [],
      ],
      'default_widget' => 'options_select',
      'default_formatter' => 'blockreference_default',
    ],
  ];
}

/**
 * Callback to setup Entity API's field properties.
 */
function blockreference_field_entity_property_callback(&$info, $entity_type, $field, $instance, $field_type) {
  $property = &$info[$entity_type]['bundles'][$instance['bundle']]['properties'][$field['field_name']];
  // Define a data structure
  $property['getter callback'] = 'entity_metadata_field_verbatim_get';
  $property['setter callback'] = 'entity_metadata_field_verbatim_set';

  $property['property info'] = blockreference_field_item_property_info();
  unset($property['query callback']);
}

/**
 * Defines info for the properties of the link-field item data structure.
 */
function blockreference_field_item_property_info() {
  $properties['moddelta'] = [
    'type' => 'text',
    'label' => t('The module & delta of the block.'),
    'setter callback' => 'entity_property_verbatim_set',
  ];
  return $properties;
}

/**
 * Implements hook_field_schema().
 */
function blockreference_field_schema($field) {
  return [
    'columns' => [
      'moddelta' => [
        'type' => 'varchar',
        'length' => 129, // 4 x 32 + 1 should be enough
        'not null' => TRUE,
        'default' => '',
      ],
    ],
    'indexes' => [
      'moddelta' => ['moddelta'],
    ],
  ];
}

/**
 * Implements hook_field_is_empty().
 */
function blockreference_field_is_empty($item, $field) {
  return !@$item['moddelta'];
}

/**
 * Implements hook_field_formatter_info().
 */
function blockreference_field_formatter_info() {
  $base = [
    'field types' => ['blockreference'],
    'settings' => ['show_empty_blocks' => FALSE],
  ];

  return [
    'blockreference_default' => [
        'label' => t('Default (title and content)'),
        'description' => t('Display the title and content of a block.'),
      ] + $base,
    'blockreference_without_title' => [
        'label' => t('Content only'),
        'description' => t('Display the content of a block.  Do not display the title.'),
      ] + $base,
    'blockreference_title' => [
        'label' => t('Title only'),
        'description' => t('Display the title of a block.  Do not display the content.'),
      ] + $base,
    'blockreference_plain' => [
        'label' => t('Info'),
        'description' => t('Display the info text of a block.'),
      ] + $base,
    'blockreference_config_link' => [
      'label' => t('Link to configuration'),
      'description' => t('Link to configure the block'),
      'field types' => ['blockreference'],
      'settings' => [
        'label' => 'default',
        'custom_label' => '',
        'destination' => 1,
      ],
    ],
  ];
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function blockreference_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary = [];

  if ($display['type'] == 'blockreference_config_link') {
    $summary[] = t('Label: @label', ['@label' => $settings['label']]);
    $summary[] = $settings['destination'] ? t('with <code>?destination</code>') : t('no <code>?destination</code>');
  }

  if (isset($settings['show_empty_blocks'])) {
    $summary[] = $settings['show_empty_blocks'] ? t('Show empty blocks') : t('Hide empty blocks (by pre-rendering)');
  }

  return implode('<br>', $summary);
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function blockreference_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $element = [];

  if ($display['type'] == 'blockreference_config_link') {
    $element['label'] = [
      '#type' => 'select',
      '#title' => t('Label'),
      '#options' => drupal_map_assoc([
        'default',
        'custom',
        'info',
        'config',
        'rendered',
      ]),
      '#default_value' => $settings['label'],
      '#attributes' => ['class' => ['blockreference-label-type']],
    ];
    $element['custom_label'] = [
      '#type' => 'textfield',
      '#title' => t('Custom label'),
      '#default_value' => $settings['custom_label'],
      '#description' => t('If empty, the default will be used: &quot;configure block&quot;'),
      '#states' => [
        'visible' => [
          'select.blockreference-label-type' => ['value' => 'custom'],
        ],
      ],
    ];

    $element['destination'] = [
      '#type' => 'checkbox',
      '#title' => t('Remember location?'),
      '#default_value' => $settings['destination'],
      '#description' => t('If checked, will append a ?destination to the URL, to come back after saving.'),
    ];

    return $element;
  }

  if (isset($settings['show_empty_blocks'])) {
    $element['show_empty_blocks'] = [
      '#type' => 'checkbox',
      '#title' => t('Show empty blocks?'),
      '#default_value' => $settings['show_empty_blocks'],
      '#description' => t("Hiding empty blocks (usually a good thing) will move up the rendering process and check its output. If the render moment is important, don't do this."),
    ];

    return $element;
  }
}

/**
 * Implements hook_field_formatter_view().
 */
function blockreference_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = [];
  $formatter = str_replace('blockreference_', '', $display['type']);
  foreach ($items as $delta => $item) {
    $vars = [
      'entity_type' => $entity_type,
      'entity' => $entity,
      'field' => $field,
      'instance' => $instance,
      'langcode' => $langcode,
      'item' => $item,
      'display' => $display,
    ];
    $element[$delta] = [
      '#theme' => 'blockreference_formatter_' . $formatter,
      '#element' => $vars,
    ];

    // To hide potentially empty/broken/missing block references, pre-render it immediately and check the output.
    if (!$display['settings']['show_empty_blocks']) {
      $html = trim(render($element[$delta]));
      if ($html) {
        $element[$delta] = [
          '#markup' => $html,
          '#blockreference_vars' => $vars,
        ];
      }
      else {
        unset($element[$delta]);
      }
    }
  }
  return $element;
}

/**
 * Implements hook_field_widget_info().
 */
function blockreference_field_widget_info() {
  return [
    'blockreference_autocomplete' => [
      'label' => t('Autocomplete text field'),
      'description' => t('Display the list of referenceable blocks as a textfield with autocomplete behaviour.'),
      'field types' => ['blockreference'],
      'settings' => [
        'size' => 60,
        'autocomplete_path' => 'blockreference/autocomplete',
      ],
    ],
  ];
}

/**
 * Implements hook_field_widget_info_alter().
 */
function blockreference_field_widget_info_alter(&$info) {
  $info['options_select']['field types'][] = 'blockreference';
  $info['options_buttons']['field types'][] = 'blockreference';

  if (module_exists('multiple_selects')) {
    $info['multiple_selects']['field types'][] = 'blockreference';
  }
}

/**
 * Implements hook_field_instance_settings_form().
 */
function blockreference_field_instance_settings_form($field, $instance) {
  $form['blockreference_modules'] = [
    '#type' => 'checkboxes',
    '#title' => t('Modules defining blocks that can be referenced'),
    '#options' => _blockreference_get_block_modules(),
    '#default_value' => _blockreference_get_block_modules_from_field($instance),
    '#description' => t('If no modules are selected, blocks from all modules will be available.'),
  ];

  return $form;
}

/**
 * Implements hook_field_widget_settings_form().
 */
function blockreference_field_widget_settings_form($field, $instance) {
  if ($instance['widget']['type'] == 'blockreference_autocomplete') {
    $form['blockreference_ac_match_method'] = [
      '#type' => 'radios',
      '#title' => t('Autocomplete match method'),
      '#options' => [
        'contains' => t('Contains string'),
        'startswith' => t('Starts with string'),
      ],
      '#default_value' => _blockreference_get_ac_match_method_from_field($instance),
    ];

    return $form;
  }
}

/**
 * Implements hook_field_widget_form().
 */
function blockreference_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  switch ($instance['widget']['type']) {
    case 'blockreference_autocomplete':
      $eid = 0;
      if (!empty($element['#entity'])) {
        list($eid) = entity_extract_ids($instance['entity_type'], $element['#entity']);
      }

      $ac_string = '';
      if (!empty($items[$delta])) {
        $item = $items[$delta];
        list($module, $delta) = explode(':', $item['moddelta']);
        $ac_string = _blockreference_block_string(_blockreference_block($module, $delta));
      }

      $element += [
        '#type' => 'textfield',
        '#default_value' => $ac_string,
        '#autocomplete_path' => $instance['widget']['settings']['autocomplete_path'] . '/' . $instance['entity_type'] . '/' . $instance['bundle'] . '/' . $instance['field_name'] . '/' . (int) $eid,
        '#size' => $instance['widget']['settings']['size'],
        '#element_validate' => ['blockreference_autocomplete_validate'],
        '#value_callback' => 'blockreference_autocomplete_value',
        '#maxlength' => 999,
      ];
      $element = ['moddelta' => $element];
      break;
  }

  return $element;
}
