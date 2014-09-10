<?php
/**
 * @file views-bootstrap-list-group-plugin-style.tpl.php
 * Default simple view template to display Bootstrap List Group.
 *
 * @ingroup views_templates
 */
?>

<<?php print $linked_items ? 'div' : 'ul'?> id="views-bootstrap-list-group-<?php print $id ?>" class="list-group <?php print $classes ?>">
  <?php foreach ($rows as $key => $row): ?>
    <<?php print $linked_items ? "a href='{$link_fields[$key]}'" : 'li'?> class="list-group-item">
      <?php print $row ?>
    </<?php print $linked_items ? 'a' : 'li'?>>
  <?php endforeach ?>
</<?php print $linked_items ? 'div' : 'ul'?>>
