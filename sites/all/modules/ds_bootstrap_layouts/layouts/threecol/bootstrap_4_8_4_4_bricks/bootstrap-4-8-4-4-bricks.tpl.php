<?php
/**
 * @file
 * Bootstrap 4-8-4-4 bricks template for Display Suite.
 */
?>

<<?php print $layout_wrapper; print $layout_attributes; ?> class="<?php print $classes; ?>">
  <?php if (isset($title_suffix['contextual_links'])): ?>
    <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>
    <div class="row">
      <?php if ($left) : ?>
      <<?php print $left_wrapper; ?> class="col-sm-4 <?php print $left_classes; ?>">
        <?php print $left; ?>
      </<?php print $left_wrapper; ?>>
        <?php endif; ?>
  <?php if ($topright) : ?>
      <<?php print $topright_wrapper; ?> class="col-sm-8 <?php print $topright_classes; ?>">
        <?php print $topright; ?>
      </<?php print $topright_wrapper; ?>>
  <?php endif; ?>
  <?php if ($bottomleft || $bottomright) : ?>
        <div class="row">
         <<?php print $bottomleft_wrapper; ?> class="col-sm-4 <?php print $bottomleft_classes; ?>">
          <?php print $bottomleft; ?>
        </<?php print $bottomleft_wrapper; ?>>
        <<?php print $bottomright_wrapper; ?> class="col-sm-4 <?php print $bottomright_classes; ?>">
          <?php print $bottomright; ?>
        </<?php print $bottomright_wrapper; ?>>
        </div>
  <?php endif; ?>
    </div>

</<?php print $layout_wrapper ?>>


<!-- Needed to activate display suite support on forms -->
<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>
