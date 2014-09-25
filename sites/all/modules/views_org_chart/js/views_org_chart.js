/* 
 * Get structure array and pass it to google chart api.
 */

(function (jQuery) {
        google.load('visualization', '1', {packages:['orgchart']});

  Drupal.behaviors.views_org_chart = {
    attach: function (context, settings) {
      google.setOnLoadCallback(this.drawChart);
       },  
drawChart: function () {
        var data = new google.visualization.DataTable();
        data.addColumn('string', 'Name');
        data.addColumn('string', 'Manager');
        data.addColumn('string', 'ToolTip');
        var out = eval('(' + Drupal.settings.views_org_chart.data + ')');
       // alert(JSON.stringify(data, null, 2));
        data.addRows(out);
        var chart = new google.visualization.OrgChart(document.getElementById(Drupal.settings.views_org_chart.cssID));
        var opt = eval('(' + Drupal.settings.views_org_chart.optional + ')');
       opt.allowHtml = true;
        chart.draw(data, opt);
      },               
  };
})(jQuery);
