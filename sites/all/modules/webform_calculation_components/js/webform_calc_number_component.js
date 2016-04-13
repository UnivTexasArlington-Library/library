(function($, Drupal)
/**
 * @file
 * JavaScript behaviors for the calculation of selected webform component numbers.
 */
{
// Our function name is prototyped as part of the Drupal.ajax namespace, adding to the commands:
  Drupal.ajax.prototype.commands.webformCalcNumberComponentAjaxCallback = function(ajax, response, status) {
// The value we passed in our Ajax callback function will be available inside
// the response object. Since we defined it as selectedValue in our callback,
// it will be available in response.selectedValue. Usually we would not use
// an alert() function as we could use ajax_command_alert() to do it without
// having to define a custom ajax command, but for the purpose of demonstration,
// we will use an alert() function here:
// alert("hello from webform calculation number component ajax commands");
// console.log("response > %o",response);
    var operand_id = '#' + response.webformOperationDataArray['operand_id'];
    var operation = response.webformOperationDataArray['operation'];
    var result_id = '#' + response.webformOperationDataArray['result_id'];
    var operation_result = 0;
// Reset the variable result field if the input result field is empty.
    if ($(result_id).val() == '') {
      if (operation == 'addition' || operation == 'subtraction') {
        result_id_value = 0;
      }
      if (operation == 'multiplication' || operation == 'division' || operation == 'percentage' || operation == 'modulo') {
        result_id_value = 1;
      }
    }
    else {
      result_id_value = Number($(result_id).val());
    }
    switch(operation) {
      case 'addition':
      operation_result = result_id_value + Number($(operand_id).val());
      break;

      case 'subtraction':
      operation_result = result_id_value - Number($(operand_id).val());
      break;

      case 'multiplication':
      operation_result = result_id_value * Number($(operand_id).val());
      break;

      case 'division':
      operation_result = result_id_value / ((Number($(operand_id).val()) == 0)? 1 : Number($(operand_id).val()));
      break;

      case 'percentage':
      operation_result = 0.01 * result_id_value * Number($(operand_id).val());
      break;

      case 'modulo':
      operation_result = Math.floor(result_id_value) % ((Number($(operand_id).val()) == 0)? 1 : Number($(operand_id).val()));
      break;
    }
    $(result_id).val(operation_result);
  };
}(jQuery, Drupal));
