<?php

/**
 * @file
 * Theme function for enhence the views admin interface vor PDF options.
 */


/**
 * Theme function to style the table UI in the Table Style Settings pages in the
 * view editing form.
 */
function theme_views_pdf_plugin_style_table($variables) {
  $form = $variables['form'];

  $output = drupal_render($form['description_markup']);

  $defheader = array(
    '',
    t('Header Style'),
    t('Body Style'),
    '',
  );
  $header = array(
    t('Field'),
    t('Header Style'),
    t('Body Style'),
    t('Width'),
    t('Hide if Empty'),
  );
  //$output .= print_r($variables, 1);

  $defrows = $rows = array();
  foreach (element_children($form['info']) as $id) {
    if ($id == '_default_') {
      $defrow = array();
      $defrow[] = array('width' => '15%');
      $defrow[] = array('data' => drupal_render($form['info'][$id]['header_style']), 'width' => '30%');
      $defrow[] = array('data' => drupal_render($form['info'][$id]['body_style']), 'width' => '30%');
      $defrow[] = array('width' => '25%');

      $defrows[] = $defrow;
    }
    else {
      $row = array();
      $row[] = array('data' => drupal_render($form['info'][$id]['name']), 'width' => '15%');
      $row[] = array('data' => drupal_render($form['info'][$id]['header_style']), 'width' => '30%');
      $row[] = array('data' => drupal_render($form['info'][$id]['body_style']), 'width' => '30%');
      $row[] = array('data' => drupal_render($form['info'][$id]['position']), 'width' => '15%');
      $row[] = array('data' => drupal_render($form['info'][$id]['empty']), 'width' => '10%');

      $rows[] = $row;
    }
  }

  $table_vars = array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array(),
    'caption' => '',
    'colgroups' => array(),
    'sticky' => 0,
    'empty' => '',
  );

  $fs_columns = array(
    'element' => array(
      '#title' => t('Column specifics'),
      '#attributes' => array(
        'class' => array(
          'collapsible',
          'collapsed',
        )
      ),
      '#children' => theme_table($table_vars),
    ),
  );

  // Use the table theme to output just a heading in consistent style.
  $table_vars['header'] = array('data' => t('Column defaults'));
  $table_vars['rows'] = array();
  $output .= theme_table($table_vars);

  // Table of header and body defaults.
  $table_vars['header'] = $defheader;
  $table_vars['rows'] = $defrows;
  $output .= theme_table($table_vars);
  // Table of header and body specifics in a fieldset.
  $output .= theme_fieldset($fs_columns);
  // The rest of the form.
  $output .= drupal_render_children($form);
  return $output;

}

/**
 * Return a list of available PDFs.
 *
 * Return value is a sorted array, keyed by the full name of the file,
 * values are the names without extensions.
 *
 * The PDF storage path is returned via the reference argument.
 */
function _list_pdfs(&$pdf_dir) {
  $pdf_dir = variable_get('views_pdf_template_stream', 'public://views_pdf_templates');

  $pdfs = views_pdf_get_pdf_templates();
  asort($pdfs);
  return $pdfs;
}

/**
 * Page to manage PDF templates.
 */
function views_pdf_templates($form, &$form_state) {

  $rows = array();
  foreach (_list_pdfs($pdf_dir) as $file_name => $name) {
    $rows[] = array(
      array('data' => l($name, file_create_url("$pdf_dir/$file_name"))),
      array('data' => l(t('Delete'), "admin/structure/views/pdfs/delete/$file_name")),
    );
  }

  $form['decription']['#markup'] =
    t('<h4>The files listed and uploaded here are available as templates for use in <em>PDF Page</em> view displays.</h4>');

  $form['pdf_list']['#markup'] = theme_table(array(
    'header' => array(t('Template files'), t('Action')),
    'rows' => $rows,
    'attributes' => array(),
    'caption' => '',
    'colgroups' => array(),
    'sticky' => 0,
    'empty' => '',
  ));

  $form['template_file'] = array(
    '#type' => 'file',
    '#title' => t('Upload new template file'),
    '#description' => t('Select a PDF to upload for use as a template'),
  );

  $form['pdf_dir'] = array(
    '#type' => 'value',
    '#value' => $pdf_dir,
  );

  $form['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Upload'),
      '#submit' => array('views_pdf_templates_submit'),
    ),
  );

  return $form;
}

/**
 * Page to manage PDF templates.
 */
function views_pdf_templates_submit($form, &$form_state) {
   $pdf_dir = $form_state['values']['pdf_dir'];

  if (file_prepare_directory($pdf_dir, FILE_CREATE_DIRECTORY)) {
    $file = file_save_upload('template_file', array('file_validate_extensions' => array('pdf')), $pdf_dir, FILE_EXISTS_ERROR);
    if (is_object($file)) {
      $file->status = FILE_STATUS_PERMANENT;
      file_save($file);
    }
  }
}

/**
 * Delete a PDF template.
 */
function views_pdf_template_delete($form, &$form_state, $file_name) {

  $pdfs = _list_pdfs($pdf_dir);
  if (isset($pdfs[$file_name])) {

    $form['name'] = array(
      '#type' => 'value',
      '#value' => $file_name,
    );
    $form['pdf_uri'] = array(
      '#type' => 'value',
      '#value' => "$pdf_dir/$file_name",
    );
    return confirm_form($form,
    t('Are you sure you want to delete the template file %name?', array('%name' => $file_name)),
      'admin/structure/views/pdfs'
    );
  }
}

/**
 * Submit function for delete confirmation.
 */
function views_pdf_template_delete_submit($form, &$form_state) {
  $uri = $form_state['values']['pdf_uri'];
  $files = file_load_multiple(array(), array('uri' => $uri));
  if ($file = reset($files)) {
    file_delete($file);
  }
  else {
    // No file record - unmanaged?
    unlink(drupal_realpath($uri));
  }
  drupal_set_message(t('PDF template %name deleted', array('%name' => $form_state['values']['name'])));
  $form_state['redirect'] = 'admin/structure/views/pdfs';
}
