//for homepage search box 
function changeSearch(tabID) {
	jQuery(".search-buttons button").removeClass('active');
	jQuery("#" + tabID).addClass('active');
	if (tabID == 'everything') {
		jQuery("#searchbox").html('<script type="text/javascript" id="s5aecdba01c2c01320001441ea15aa1ac" src="http://uta.summon.serialssolutions.com/widgets/box.js"></script><script type="text/javascript"> new SummonCustomSearchBox({"id":"#s5aecdba01c2c01320001441ea15aa1ac","params":{"keep_r":true},"colors":{},"searchbutton_text":"Go","advanced_text":"Advanced Search","placeholder_text":"Search articles, books, guides, and more","advanced":"true","suggest":"true","popup":"true"})</script>');
		jQuery("#s5aecdba01c2c01320001441ea15aa1ac .summon-search-submit[0]").attr("onclick", "_gaq.push(['_trackEvent', 'search', 'submit', 'summoneverything']);");
	}
	if (tabID == 'articles') {
		jQuery("#searchbox").html('<script id="s5b6f3640cedb0131542b00237dd8628a" src="http://uta.summon.serialssolutions.com/widgets/box.js" type="text/javascript" ></script><script type="text/javascript">new SummonCustomSearchBox({"id":"#s5b6f3640cedb0131542b00237dd8628a","params":{"s.fvf[]":["ContentType,Journal Article"],"keep_r":true},"colors":{},"searchbutton_text":"Go","advanced_text":"Advanced Search","placeholder_text":"Search articles","advanced":"true","suggest":"true","popup":"true"})</script><div class="search-parameters"><label><input type="checkbox" id="peerreview" name="peerbox" onclick="peer();">Peer-Reviewed Only</label></div>');
		jQuery("#s5b6f3640cedb0131542b00237dd8628a .summon-search-submit[0]").attr("onclick", "_gaq.push(['_trackEvent', 'search', 'submit', 'summonarticles']);");
	}
	if (tabID == 'books') {
		jQuery("#searchbox").html('<script id="s5da153d0cede013143c5441ea15a6074" src="http://uta.summon.serialssolutions.com/widgets/box.js" type="text/javascript" ></script><script type="text/javascript">new SummonCustomSearchBox({"id":"#s5da153d0cede013143c5441ea15a6074","params":{"s.fvf[]":["ContentType,Book / eBook"],"keep_r":true},"colors":{},"searchbutton_text":"Go","advanced_text":"Advanced Search","placeholder_text":"Search books","advanced":"true","suggest":"true","popup":"true"})</script><div class="search-parameters"><label><input id="ebookcheck" name="ebookbox" onclick="expand()" type="checkbox">E-Book only</label> <label><input id="expandcheck" name="expandbox" onclick="expand()" type="checkbox">Expand beyond the Libraries\' collection</label></div>');
		jQuery("#s5da153d0cede013143c5441ea15a6074 .summon-search-submit[0]").attr("onclick", "_gaq.push(['_trackEvent', 'search', 'submit', 'summonbooks']);");
	}
} 

// for new homepage searchbox
/* $(document).ready(function () {
  $("#hider").hide();
  $("#hiderarticles").hide();
    });
$("#books").click(function(){
  $("#hiderarticles").hide();
  $('#hider').show();
  
});
$("#everything").click(function(){
  $("#hiderarticles").hide();
  $('#hider').hide();
});
$("#articles").click(function(){
  $('#hider').hide();
  $("#hiderarticles").show();
}); */


//for getting individual count of everything summon search in google analytics
jQuery(document).ready(function($) {
	$("#s5aecdba01c2c01320001441ea15aa1ac .summon-search-submit[0]").attr("onclick", "_gaq.push(['_trackEvent', 'search', 'submit', 'summoneverything']);");
});


function peer() {
	//peer review checkbox functionality
		if (jQuery("#peerreview").prop("checked")) {
			new SummonCustomSearchBox({"id":"#s5b6f3640cedb0131542b00237dd8628a","params":{"s.fvf[]":["ContentType,Journal Article","IsPeerReviewed,true"],"keep_r":true},"colors":{},"searchbutton_text":"Go","advanced_text":"Advanced Search","placeholder_text":"Search peer-reviewed articles","advanced":"true","suggest":"true","popup":"true"})
		} else {
			new SummonCustomSearchBox({"id":"#s5b6f3640cedb0131542b00237dd8628a","params":{"s.fvf[]":["ContentType,Journal Article"],"keep_r":true},"colors":{},"searchbutton_text":"Go","advanced_text":"Advanced Search","placeholder_text":"Search articles","advanced":"true","suggest":"true","popup":"true"})
		}
		jQuery("#s5b6f3640cedb0131542b00237dd8628a .summon-search-submit[0]").attr("onclick", "_gaq.push(['_trackEvent', 'search', 'submit', 'summonarticles']);");
		jQuery("#s5b6f3640cedb0131542b00237dd8628a").attr('action', 'http://uta.summon.serialssolutions.com/search');
		jQuery("#s5b6f3640cedb0131542b00237dd8628a a").attr('href', 'http://uta.summon.serialssolutions.com/advanced');
}

function expand() {
	if (jQuery("#ebookcheck").prop('checked') && jQuery("#expandcheck").prop('checked')) {
  		new SummonCustomSearchBox({"id":"#s5da153d0cede013143c5441ea15a6074","params":{"s.fvf[]":["IsFullText,true","ContentType,Book / eBook"],"s.ho":["f"],"keep_r":true},"colors":{},"tagline_text":"","searchbutton_text":"Go","advanced_text":"Advanced Search","placeholder_text":"Search ebooks and beyond","advanced":"true","suggest":"true","popup":"true"})
    } 
    else if (jQuery("#ebookcheck").prop('checked') && !jQuery("#expandcheck").prop('checked')) {
		new SummonCustomSearchBox({"id":"#s5da153d0cede013143c5441ea15a6074","params":{"s.fvf[]":["IsFullText,true","ContentType,Book / eBook"],"keep_r":true},"colors":{},"tagline_text":"","searchbutton_text":"Go","advanced_text":"Advanced Search","placeholder_text":"Search ebooks","advanced":"true","suggest":"true","popup":"true"})
    }   
    else if (jQuery("#expandcheck").prop('checked') && !jQuery("#ebookcheck").prop('checked')) {
     	new SummonCustomSearchBox({"id":"#s5da153d0cede013143c5441ea15a6074","params":{"s.fvf[]":["ContentType,Book / eBook"],"s.ho":["f"],"keep_r":true},"colors":{},"tagline_text":"","searchbutton_text":"Go","advanced_text":"Advanced Search","placeholder_text":"Search books and beyond","advanced":"true","suggest":"true","popup":"true"})
    } else {
		new SummonCustomSearchBox({"id":"#s5da153d0cede013143c5441ea15a6074","params":{"s.fvf[]":["ContentType,Book / eBook"],"keep_r":true},"colors":{},"tagline_text":"","searchbutton_text":"Go","advanced_text":"Advanced Search","placeholder_text":"Search books","advanced":"true","suggest":"true","popup":"true"})
    } 
   		jQuery("#s5da153d0cede013143c5441ea15a6074 .summon-search-submit[0]").attr("onclick", "_gaq.push(['_trackEvent', 'search', 'submit', 'summonbooks']);");
		jQuery("#s5da153d0cede013143c5441ea15a6074").attr('action', 'http://uta.summon.serialssolutions.com/search');
		jQuery("#s5da153d0cede013143c5441ea15a6074 a").attr('href', 'http://uta.summon.serialssolutions.com/advanced');
}