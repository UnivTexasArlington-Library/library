<?php
drupal_add_js(array('views_org_chart' => array('data' => drupal_json_encode($views_org_chart_row))), 'setting');
?>
<div id="<?php echo $views_org_chart_cssid; ?>"></div>