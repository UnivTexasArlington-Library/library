<?php

/**
 * @file
 * Support for processing blockreference fields in Migrate.
 */

class MigrateBlockReferenceFieldHandler extends MigrateSimpleFieldHandler {

  public function __construct($options = []) {
    parent::__construct([
      'value_key' => 'moddelta',
      'skip_empty' => TRUE,
    ]);

    $this->registerTypes(['blockreference']);
  }
}
