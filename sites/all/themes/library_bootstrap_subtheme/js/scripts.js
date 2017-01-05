jQuery(document).ready(function($) {
  $('[data-toggle=offcanvas]').click(function() {
    $('.row-offcanvas').toggleClass('active');
  });
  $(".dropdown.first").addClass("open");
   var winwidth = $(window).width();
	 if (winwidth < 992) {
		$(".region-sidebar-second").appendTo(".region-sidebar-first");
		$(".sidebar_second").addClass("pull-left").removeClass("pull-right"); 
	 } else {
		$(".region-sidebar-second").appendTo(".sidebar_second");
	 }
	$(window).resize(function() {
	 winwidth = $(window).width();
	 if (winwidth < 992) {
		$(".region-sidebar-second").appendTo(".region-sidebar-first");
		$(".sidebar_second").addClass("pull-left").removeClass("pull-right"); 
	 } else {
		$(".region-sidebar-second").appendTo(".sidebar_second");
		$(".sidebar_second").addClass("pull-right").removeClass("pull-left"); 
	 }
  });

//closing menu's initially
	$("#block-menu-menu-right-menu-bottom-var-1 .menu").toggle();
	$("#block-menu-menu-bottom-left-menu-var-1 .menu").toggle();

	$("#block-menu-menu-left-menu-bottom-var-1 .menu").toggle();


$("#block-menu-menu-left-menu-top .block-title-link").append(" <span class='caret'></span>");
$("#block-menu-menu-left-menu-bottom .block-title-link").append(" <span class='caret'></span>");
//services menu fix @upendra

$("#block-menu-menu-left-menu-bottom-var-1 .block-title-link").append(" <span class='caret'></span>");
$("#block-menu-menu-bottom-left-menu-var-1 .block-title-link").append(" <span class='caret'></span>");
$("#block-menu-menu-right-menu-top-var-1 .block-title-link").append(" <span class='caret'></span>");
$("#block-menu-menu-right-menu-bottom-var-1 .block-title-link").append(" <span class='caret'></span>");

//
$("#block-menu-menu-right-menu-top .block-title-link").append(" <span class='caret'></span>");
$("#block-menu-menu-right-menu-bottom .block-title-link").append(" <span class='caret'></span>");
$("#block-menu-menu-left-menu-top .block-title-link").on("click", function(e) {
	e.preventDefault();
	$("#block-menu-menu-left-menu-top .menu").toggle();
	$("#block-menu-menu-left-menu-top .caret").toggleClass("up");
});
$("#block-menu-menu-left-menu-bottom .block-title-link").on("click", function(e) {
	e.preventDefault();
	$("#block-menu-menu-left-menu-bottom .menu").toggle();
	$("#block-menu-menu-left-menu-bottom .caret").toggleClass("up");
});
//
//caret toggle fix @upendra
$("#block-menu-menu-bottom-left-menu-var-1 .block-title-link").on("click", function(e) {
	e.preventDefault();
	$("#block-menu-menu-bottom-left-menu-var-1 .menu").toggle();
	$("#block-menu-menu-bottom-left-menu-var-1 .caret").toggleClass("up");
});

$("#block-menu-menu-left-menu-bottom-var-1 .block-title-link").on("click", function(e) {
	e.preventDefault();
	$("#block-menu-menu-left-menu-bottom-var-1 .menu").toggle();
	$("#block-menu-menu-left-menu-bottom-var-1 .caret").toggleClass("up");
});
$("#block-menu-menu-right-menu-top-var-1 .block-title-link").on("click", function(e) {
	e.preventDefault();
	$("#block-menu-menu-right-menu-top-var-1 .menu").toggle();
	$("#block-menu-menu-right-menu-top-var-1 .caret").toggleClass("up");
});
$("#block-menu-menu-right-menu-bottom-var-1 .block-title-link").on("click", function(e) {
	e.preventDefault();
	$("#block-menu-menu-right-menu-bottom-var-1 .menu").toggle();
	$("#block-menu-menu-right-menu-bottom-var-1 .caret").toggleClass("up");
});

//


$("#block-menu-menu-right-menu-top .block-title-link").on("click", function(e) {
	e.preventDefault();
	$("#block-menu-menu-right-menu-top .menu").toggle();
	$("#block-menu-menu-right-menu-top .caret").toggleClass("up");
});
$("#block-menu-menu-right-menu-bottom .block-title-link").on("click", function(e) {
	e.preventDefault();
	$("#block-menu-menu-right-menu-bottom .menu").toggle();
	$("#block-menu-menu-right-menu-bottom .caret").toggleClass("up");
});

//adds pager class to book navigation
$(".book-navigation .page-links").addClass("pager");

//adds hours icon to all hours link on homepage
$(".hours a:last-of-type").prepend('<span class="glyphicon glyphicon-time"></span>');
});

