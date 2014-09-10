<div id="views-bootstrap-carousel-<?php print $id ?>" class="<?php print $classes ?>" <?php print $attributes ?>>
<?php $rows_count = count($rows); ?>
<?php $item_count = 3; ?>
<?php $cl = "col-xs-".(int)(12/$item_count); ?>
<?php #można by tu dorobić logikę jak chcemy mieć różną wartość item count // jakieś jquer, które by to zawijało ładnie.... ?>
  <?php if ($indicators): ?>
    <!-- Carousel indicators -->
    <ol class="carousel-indicators">
    <?php $k = 0; ?>
<?php for ($i = 0; $i < $rows_count; $i += $item_count): ?>
    <li data-target="#views-bootstrap-carousel-<?php print $id ?>"
        data-slide-to="<?php print $k++ ?>"
        class="<?php if ($k == 0) print 'active' ?>"></li>
  <?php endfor; ?>
    </ol>
  <?php endif ?>
<div class="carousel-inner">
<?php if ($rows_count % $item_count== 1): ?>
<?php for($i=0;$i<$rows_count-1;$i+=$item_count):?>
    <div class="item <?php if ($i == 0) print 'active' ?>">
          <?php for($j=0;$j<$item_count;$j++): ?>
              <div class="<?php print $cl; ?>">
<?php print $rows[$i+$j]?>
              </div>
            <?php endfor; ?>
        </div>
<?php endfor; ?>
      <div class="item">
             <?php #Imitacja karuzeli: ostatni + dwa pierwsze - poszukac rozwiązania żeby to była prawdziwa karuzela?>
          <div class="<?php print $cl; ?>">
<?php print $rows[$rows_count-1]?>
            </div>
            <div class="<?php print $cl; ?>">
          <?php print $rows[0]?>
            </div>
            <div class="<?php print $cl; ?>">
          <?php print $rows[1]?>
          </div>
      </div>
<?php elseif($rows_count % $item_count == 2):?>
<?php for($i=0;$i<$rows_count-2;$i+=$item_count):?>
    <div class="item <?php if ($i == 0) print 'active' ?>">
          <?php for($j=0;$j<$item_count;$j++): ?>
              <div class="<?php print $cl; ?>">
<?php print $rows[$i+$j]?>
              </div>
            <?php endfor; ?>
        </div>
<?php endfor; ?>
    <div class="item">
             <?php #Imitacja karuzeli: ostatni + dwa pierwsze - poszukac rozwiązania żeby to była prawdziwa karuzela?>
          <div class="<?php print $cl; ?>">
<?php print $rows[$rows_count-2]?>
            </div>
            <div class="<?php print $cl; ?>">
          <?php print $rows[$rows_count-1]?>
            </div>
            <div class="<?php print $cl; ?>">
          <?php print $rows[0]?>
          </div>
      </div>
<?php else:?>
<?php for($i=0;$i<$rows_count;$i+=$item_count):?>
    <div class="item <?php if ($i == 0) print 'active' ?>">
          <?php for($j=0;$j<$item_count;$j++): ?>
              <div class="<?php print $cl; ?>">
<?php print $rows[$i+$j]?>
              </div>
            <?php endfor; ?>
        </div>
<?php endfor; ?>
<?php endif ?>
</div>
 <!-- Carousel items -->
  <?php if ($navigation): ?>
    <!-- Carousel navigation -->
    <a class="carousel-control left" href="#views-bootstrap-carousel-<?php print $id ?>" data-slide="prev">
      <span class="icon-prev"></span>
    </a>
    <a class="carousel-control right" href="#views-bootstrap-carousel-<?php print $id ?>" data-slide="next">
      <span class="icon-next"></span>
    </a>
  <?php endif ?>
</div>