<?php
/**
 * @file
 * Handles the arrays passed in the webform node.
 */

class WebformCalculationComponentsFormTree {

  /**
   * Constructor function.
   */

  public function __construct() {
  }

  /**
   * Builds up a tree path to insert AJAX attributes.
   *
   * @param array $components_tree
   *   The array of components in a tree shape taken from the webform node form
   *   array. It will be used to build up the path array to insert the AJAX
   *   attributes.
   * @param array $tree_path
   *   An array with the cid (Component Id) of the current wb_calc component
   *   as the key and the current wb_calc component form key as the value.
   * @param string $wb_calc_comp_pid
   *   The pid (Parent Id) of the wb_calc component that calls this
   *   function.
   *
   * @return array
   *   It returns an unidimensional array (complete) with the list of component
   *   form keys that specifies the tree path. It will be used to insert the AJAX
   *   attributes.
   */
  function buildTreePath(array $components_tree, array $tree_path, $wb_calc_comp_pid) {
    // Return if there is not a fieldset parent.
    if ($wb_calc_comp_pid == 0) {
      return $tree_path;
    }
    // The highest branch of the tree path is stored.
    $tree_path_first_index = (int) $wb_calc_comp_pid;
    // We loop until the root is reached.
    while ($tree_path_first_index != 0) {
      // The parent fieldset is isolated in one array.
      array_unshift($tree_path, $components_tree[$tree_path_first_index]['form_key']);
      $tree_path_first_index = (int) $components_tree[$tree_path_first_index]['pid'];
    }
    return $tree_path;
  }

  /**
   * Inserts new attributes in the argument array.
   *
   * @param array $form_submitted_array
   *   The submitted array where the components are stored.
   * @param array $tree_path
   *   The list of components forming a tree path to select the form element
   *   where we need to insert the new attribute.
   *   The list contains form keys.
   * @param array $new_attributes
   *   An associative array to insert in the specified tree path.
   *
   * @return bool
   *   It returns true if the new attributes have been inserted and false if not.
   */
  function insertNewAttribute(array &$form_submitted_array, array $tree_path, array $new_attributes) {
    $aux = &$form_submitted_array;
    foreach ($tree_path as $key) {
      if (isset($aux[$key])) {
        $aux = &$aux[$key];
      }
      // If the path is not correct return false.
      else {
        return FALSE;
      }
    }
    if (is_array($aux) && isset($new_attributes)) {
      foreach ($new_attributes as $new_attribute_key => $new_attribute_value) {
        $aux[$new_attribute_key] = $new_attribute_value;
      }
    }
    return TRUE;
  }

  /**
   * Gets the pid (Parent Id) of the calculation component.
   *
   * @param array $components
   *   The array of components in a tree shape taken from the webform node form
   *   array.
   * @param string $form_key
   *   The form key string to get the cid (Component Id), and then the pid.
   * @param boolean $include_fieldset
   *   Because webform allows that a fieldset and another component shares the
   *   same form_key, most of the times we have to check that the component type
   *   is not a fieldset, that is why this parameter is set to false by default.
   *
   * @return string
   *   It returns the pid string.
   */
  function getPid(array $components, $form_key, $include_fieldset = FALSE) {
    foreach ($components as $component) {
      if ($component['form_key'] == $form_key) {
        if (($include_fieldset == FALSE && $component['type'] != 'fieldset') ||
          ($include_fieldset == TRUE)) {
          return $component['pid'];
        }
      }
    }
  }

  /**
   * Builds up an array with the necessary data of the calculation elements.
   *
   * This helper function buid up an array to store the necessary data to select
   * the elements involved in the calculation.
   *
   * Since the selectors for calculating the result via AJAX can have different
   * paths because they are located under different parent fieldsets, we need to
   * create the selector based on the corresponding tree path of the component.
   * Examples of those components are the operand fields and the result field.
   *
   * @param array $components
   *   The array of components in a tree shape taken from the webform node form
   *   array.
   * @param string $wb_calc_component_cid
   *   The cid (Component Id) of the calculation component where the operands,
   *   operation, result fields etc. is stored.
   *
   * @return array
   *   It returns the an array that contains the operand and result fields
   *   selectors (in an tree path array) and the operation to perform.
   */
  function getOperationData(array $components, $wb_calc_component_cid) {
    // Calculation Operation Component array
    $calc_op_comp = array();
    if ($components[$wb_calc_component_cid]['type'] == 'wb_calc_number') {
      $calc_op_comp['operand_field_path'] = $this->buildTreePath($components, array($components[$wb_calc_component_cid]['form_key']), $components[$wb_calc_component_cid]['pid']);
    }
    if ($components[$wb_calc_component_cid]['type'] == 'wb_calc_hidden') {
      foreach ($components[$wb_calc_component_cid]['extra']['first_operand'] as $first_operand) {
        $calc_op_comp['first_operand_paths'][] = $this->buildTreePath($components, array($first_operand), $this->getPid($components, $first_operand));
      }
      foreach ($components[$wb_calc_component_cid]['extra']['second_operand'] as $second_operand) {
        $calc_op_comp['second_operand_paths'][] = $this->buildTreePath($components, array($second_operand), $this->getPid($components, $second_operand));
      }
      $select_field_pid = $this->getPid($components, $components[$wb_calc_component_cid]['extra']['select_field'], 'select');
      $calc_op_comp['select_field_path'] = $this->buildTreePath($components, array($components[$wb_calc_component_cid]['extra']['select_field']), $select_field_pid);
    }
    $calc_op_comp['operation_type'] = $components[$wb_calc_component_cid]['extra']['operation_type'];
    $result_field_pid = $this->getPid($components, $components[$wb_calc_component_cid]['extra']['result_field']);
    $calc_op_comp['result_field_path'] = $this->buildTreePath($components, array($components[$wb_calc_component_cid]['extra']['result_field']), $result_field_pid);
    return $calc_op_comp;
  }

}
