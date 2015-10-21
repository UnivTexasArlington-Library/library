<?php
/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see bootstrap_preprocess_page()
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see bootstrap_process_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */
?>

<div class="page-container container-fluid">
          <?php if (!empty($page['lib_header'])): ?>
        <div class="row">
      <?php if (!empty($page['feedback'])): ?>
        <div class="col-md-2 col-sm-3 hidden-xs">
          <?php print render($page['feedback']); ?>
        </div>
        <div class="col-md-5 col-sm-6 col-xs-12 uta_header">

      <?php else: ?>
        <div class="col-md-5 col-sm-6 col-xs-12 uta_header col-sm-offset-3 col-md-offset-2">
      <?php endif; ?>
        <?php print render($page['lib_header']); ?>
        </div>


        <?php if (!empty($page['todays_hrs'])): ?>
        <div class="row">
          <div class="col-md-3 col-sm-3 col-xs-12">
            <?php print render($page['todays_hrs']); ?>
          </div>
        </div>
      <?php endif; ?>
      

      </div>
      <?php endif; ?>
      <?php if (!empty($page['univ_logo'])): ?>
        <div class="row">
          <div class="col-md-5 col-md-offset-2 col-sm-6 col-sm-offset-3 col-xs-12 univ_logo">
            <?php print render($page['univ_logo']); ?>
          </div>
        </div>
      <?php endif; ?>
      



      <?php if (!empty($page['modal'])): ?>
        <div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
          <div class="modal-dialog">
            <div class="modal-content">
              <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal"><span aria-hidden="true">&times;</span><span class="sr-only">Close</span></button>
              </div>
              <div class="modal-body">
                <?php print render($page['modal']); ?>
              </div>
              <div class="modal-footer">
                <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
              </div>
            </div>
          </div>
        </div>
      <?php endif; ?>
      <?php if (!empty($page['notification'])): ?>
        <div class="row"><div class="col-md-8 col-md-offset-2 col-sm-9 col-sm-offset-3 col-xs-12 notification"><div class='alert alert-danger'><?php print render($page['notification']); ?></div></div></div>
      <?php endif; ?>
      <div class="navbar navbar-default visible-xs" role="navigation">
       <div class="container">
      <div class="navbar-header">
           <button type="button" class="navbar-toggle" data-toggle="offcanvas" data-target=".row-offcanvas">
             <span class="icon-bar"></span>
             <span class="icon-bar"></span>
             <span class="icon-bar"></span>
           </button>
           <a class="navbar-brand" href="#"></a>
      </div>
       </div>
    </div>
  

<div id="page-content-wrapper" class="main-container" >
  <div class="row row-offcanvas row-offcanvas-left">

 <?php if (!empty($page['sidebar_first'])): ?>
      <div class="col-xs-6 col-sm-3 col-md-2 sidebar-offcanvas" role="navigation" id="sidebar">
        <?php print render($page['sidebar_first']); ?>
      </div>  <!-- /#sidebar-first -->
    <?php endif; ?>

<?php if (!empty($page['sidebar_second'])): ?>
      <div class="col-xs-6 col-sm-3 col-md-2 pull-right sidebar_second" role="navigation">
        <?php print render($page['sidebar_second']); ?>
      </div> <!-- /#sidebar-second -->
    <?php endif; ?>
    
  <header role="banner" id="page-header">
    <?php if (!empty($site_slogan)): ?>
      <p class="lead"><?php print $site_slogan; ?></p>
    <?php endif; ?>

    <?php print render($page['header']); ?>
  </header> <!-- /#page-header -->

    <div<?php //print $content_column_class; ?> class="col-md-8 col-sm-9 col-xs-12 center-container">
      
      <?php if (!empty($page['highlighted'])): ?>
        <div class="highlighted jumbotron"><?php print render($page['highlighted']); ?></div>
      <?php endif; ?>
      <?php if (!empty($breadcrumb)): print $breadcrumb; endif;?>
      <a id="main-content"></a>
      <?php print render($title_prefix); ?>
      <?php if (!empty($title)): ?>
        <!--<h1 class="page-header"><?php //print $title; ?></h1>-->
      <?php endif; ?>
      <?php print render($title_suffix); ?>
      <?php print $messages; ?>
      <?php if (!empty($tabs)): ?>
        <?php print render($tabs); ?>
      <?php endif; ?>
      <?php if (!empty($action_links)): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>
      <?php print render($page['content']); ?>
          <div class="row">
        <footer class="footer">
              <?php print render($page['footer']); ?>
        </footer>
      </div><!-- end footer row-->
    </div><!--end center container-->
  </div><!--end row -->
</div><!-- end container -->
</div><!--end -->

