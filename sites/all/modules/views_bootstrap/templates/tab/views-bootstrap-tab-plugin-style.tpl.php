<div id="views-bootstrap-tab-<?php print $id ?>" class="<?php print $classes ?>">
  <div class="tab-content">
    <?php foreach ($rows as $key => $row): ?>
      <div class="tab-pane <?php if ($key === 0) print 'active'?>" id="tab-<?php print "{$id}-{$key}" ?>">
        <?php print $row ?>
      </div>
    <?php endforeach ?>
  </div>
  <ul class="nav nav-<?php print $tab_type?> <?php if ($justified) print 'nav-justified' ?>">
    <?php foreach ($tabs as $key => $tab): ?>
     <li class="<?php if ($key === 0) print 'active'?>">
       <a href="#tab-<?php print "{$id}-{$key}" ?>" data-toggle="tab"><?php print $tab ?></a>
     </li>
    <?php endforeach ?>
  </ul>
</div>

