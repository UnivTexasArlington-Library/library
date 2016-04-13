(function($, Drupal)
/**
 * @file
 * JavaScript behaviors for the calculation of selected webform component numbers.
 */
{
  /**
   * Calculate two numbers according to the corresponding arithmetic operation.
   *
   * @param number $operand_one
   *   The number to be calculated in the first position of the arithmetic
   *   operation. The result is different in case of non commutative operations
   *   like subtraction, division etc.
   * @param number $operand_two
   *   The number to be calculated in the second position of the arithmetic
   *   operation.
   * @param string $operation
   *   The operation to be performed with the operands e.g. addition,
   *   subtraction, multiplication etc.
   *
   * @return number
   *   It returns the result of the operation.
   */
   function calculate_two_numbers(operand_one, operand_two, operation) {
    var result = 0;
    switch (operation) {
      case 'addition':
        result = (operand_one + operand_two);
        break;
      case 'subtraction':
        result = (operand_one - operand_two);
        break;
      case 'multiplication':
        result = (operand_one * operand_two);
        break;
      case 'division':
      // Prevent division by 0
        if(operand_two == 0) {
          operand_two = 1;
        }
        result = (operand_one / operand_two);
        break;
      case 'percentage':
        result = 0.01 * operand_one * operand_two;
        break;
      case 'modulo':
      // Prevent division by 0
        if(operand_two == 0) {
          operand_two = 1;
        }
        result = Math.floor(operand_one) % Math.floor(operand_two);
        break;
      }
    return result;
  }
  /**
   * Get the current number of the input form field.
   *
   * @param string $field_id
   *   The Id of the input form field to get the value from.
   * @param integer $neutral_number
   *   The neutral number in case that the field is empty. It differs depending
   *   on the operation.
   *
   * @return number
   *   It returns the number value of the input form field.
   */
  function get_field_value(field_id, neutral_number) {
    console.log("field_id > %o",field_id);
    if (document.getElementById(field_id).value != '') {
      return Number(document.getElementById(field_id).value);
    }
    else {
      return neutral_number;
    }
  }

// Our function name is prototyped as part of the Drupal.ajax namespace, adding to the commands:
  Drupal.ajax.prototype.commands.webformCalcHiddenComponentAjaxCallback = function(ajax, response, status) {
// The value we passed in our Ajax callback function will be available inside
// the response object. Since we defined it as selectedValue in our callback,
// it will be available in response.selectedValue. Usually we would not use
// an alert() function as we could use ajax_command_alert() to do it without
// having to define a custom ajax command, but for the purpose of demonstration,
// we will use an alert() function here:
// alert("hello from Webform calculation Hidden component ajax commands");
// For debugging use: console.log("this is the variable myvar> %o",myvar);
    var operation = response.webformOperationDataArray['operation'];
    var result_id = '#' + response.webformOperationDataArray['result_id'];
    var operation_result = 0;
    var inverse_operation = "addition"; //Default operation
    var neutral_number = 0; //Default neutral number
    var operands_data = 2; //We assume that none operand array is empty
    //If operation is neither addition nor subtraction, neutral number is 1
    if (operation == "multiplication" || operation == "division" ||
      operation == "percentage" || operation == "modulo") {
      inverse_operation = "multiplication";
      neutral_number = 1;
    }
    console.log("response.webformOperationDataArray > %o",response.webformOperationDataArray);
    //We check if first_operand_ids is an Array (so it is not empty)
    if (response.webformOperationDataArray['first_operand_ids'] instanceof Array) {
      var first_operand_ids = response.webformOperationDataArray['first_operand_ids'];
      var first_operand_total = get_field_value(first_operand_ids[0], neutral_number);
      for (i=1; i < first_operand_ids.length; i++) {
        first_operand_total = calculate_two_numbers(first_operand_total, get_field_value(first_operand_ids[i], neutral_number), inverse_operation);
      }
    }
    else { //If it is empty, set the length of the array to 1
      var first_operand_total = neutral_number;
      operands_data--; //At least one operand array is empty
    }
    //We check if second_operand_ids is an Array (so it is not empty)
    if (response.webformOperationDataArray['second_operand_ids'] instanceof Array) {
      var second_operand_ids = response.webformOperationDataArray['second_operand_ids'];
      var second_operand_total = get_field_value(second_operand_ids[0], neutral_number);
      for (j=1; j < second_operand_ids.length; j++) {
        second_operand_total = calculate_two_numbers(second_operand_total, get_field_value(second_operand_ids[j], neutral_number), inverse_operation);
      }
    }
    else { //If it is empty, set the length of the array to 1
      var second_operand_total = neutral_number;
      operands_data--; //At least one operand array is empty
    }
    //It is not necessary to calculate the result if both operand arrays are empty
    if (operands_data > 0) {
      operation_result = calculate_two_numbers(first_operand_total, second_operand_total, operation);
      $(result_id).val(operation_result);
    }
    console.log("response.webformOperationDataArray > %o",response.webformOperationDataArray);
  };
}(jQuery, Drupal));
