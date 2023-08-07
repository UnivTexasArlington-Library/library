With the Views PDF module you can output a view as a PDF document. Each field of
the view can be placed on the PDF page directly in the administration interface.
Therefore a new display called "PDF" is added.

There are already some PDF solutions such as Print. But these solutions use the
HTML output and converts this to PDF. The disadvantages of such an integration
are:
    * No control over page flow (e.g. page break).
    * Little or no control over page header and footer.
    * You need HTML skills to change the layout.
    * The rendering is slow and need a lot of memory, because it need to render
      the HTML.
    * Complex tables make troubles.
    * Vector graphics can not be implemented, therefore the printing of the doc-
      ument can be problematic.
    * You are limited by HTML's capabilities.



Installation instructions:
--------------------------
   1. Download the module or checkout the module.
   2. Upload the module to your Drupal instance.
   3. Download the required libraries. Download TCPDF and FPDI. Copy the files
      to the lib directory in the module directory. The path must be so:
      "sites/all/libraries/tcpdf/tcpdf.php" respectively "sites/all/libraries/fpdi/fpdi.php".
      If you are using the Libraries API then put them into the libraries folder.
   4. Check under reports if you setup everything correct.
   5. Setup a view with a PDF display.
   6. Use it.

Basic Usage
-----------
   1. Setup a new view or use an existing view. How to do this see in the
      documentation of the Views module.
   2. In the view add the display "PDF Page".
   3. Select the new added display.
   4. Select the Style:
      a. PDF Table - place the fields in table with a table header, one record per row.
      b. PDF Unformatted - place the fields in no structured way on the PDF.
      c. PDF Unformatted Grid - place the fields in cells in a grid, one record per cell.
   5. In the settings of the style you can setup per field settings. Such as the
      position, the size of the field, the font and so on. Important: Switch to
      the PDF Page display in the default display this options does not appear.
   6. Under PDF Page Setting you can setup the size of the page.
   7. Under PDF Font Settings you can setup the default fonts for the PDF.
   8. Under PDF Template Settings you can setup a background PDF (see Templates below).
   9. To add a page break, you can add a PDF page-break field. When this field
      is rendered a new page is added. Don't give the field a label, and
      ensure it's the last field.
  10. You can find also a page number field. You can use it to print the current
      page number. Important for positioning the field in the header or footer,
      you need to set the relative position in the field settings to
      "In header / footer".
  11. There are additional settings for the header and footer styling under
      PDF Header & Footer. These allow the default font and alignment parameters
      to be defined separately for the header & footer. The Header Margin and
      Footer Spacing values define the vertical placement of the header and footer.
      For the header it's the distance from the edge of the page, for the footer
      it's the distance from the start of the bottom margin.
  12. You can embed the page number in a header or footer by using the marker !page.
      This is mainly for use in table mode, as you can't place fields in the header
      or footer so the page number field can't be used.
      Note that other variable substitutions can be achieved using the token-filter
      module, with a text format in which it's enabled.

Grid output
-----------
   Grid mode is ideal for printing things like label sheets. In grid settings you specify
   the number of rows and columns, and any spacing between. Cell size is calculated by
   fitting the specified layout within the page margins. You can also choose between
   row-first or column-first ordering.

   Field positioning is similar to unformatted mode, except that it is relative to
   the cell, not the page. Nothing is output beyond the cell boundary, anything that
   would overflow is not output at all.

   There is no option for header or footer fields as it doesn't really make sense.
   HTML is always stripped, which is necessary for cell boundary control.

Tabular output
--------------
   In PDF Table mode there are additional layout settings, for the column data and for
   the column headings. In each case you can set specific text and alignment parameters.
   You can set defaults that apply to all columns, and also override with specifics
   for individual columns. Any value not given a default or specific value will fall
   back to the PDF document settings.

   Cell padding and borders can be specified for both headers and rows.
   Padding applies above and below the text in a cell. A border surrounds any padding
   and can be specified either using "1" for a border on all sides, or a combination
   of the letters L, R, T, B to selectively add a border to any of the four sides
   ("LRTB" is the same as "1").

   You can also set a width for each column. Columns without a set width are divided
   evenly into the remaining space. The table will be sized to fit within the page
   margins, unless you set a width for every column, and the total is less than the
   width between margins.

   Column headings are optional, if specified you can define a header spacing to create
   a gap between the header and the first line.

   Row Height is optional, the default row height will be big enough to accommodate
   one line of the largest column font. An entered Row Height smaller than this will be
   overridden. If a larger Row Height is entered then all rows will be made this height.
   This can be used to allow column data to wrap onto multiple lines - as many lines
   as will fit within the height will be displayed. Data that won't fit is truncated.

   Each page will be filled with as many rows as will fit before reaching the bottom
   margin. You can, however, use the PDF page-break field. The field will not appear
   in the list of columns, but will still force a break after the set number of rows.

   Note that all rows will be the same height, even if the extra space is not filled -
   variable height rows are not supported.

   Row data is never rendered as HTML, as it's impossible to control row height if
   HTML is used. This is important to ensure correct breaking across multiple pages.

Templates
---------
   Templates are external PDF files that can be used as a background for the output,
   as well as be printed before and/or after the generated output.
   To make a PDF available as a template you must first upload it. In the main Views
   list page, there is an additional tab "PDF Templates". Use this to manage your
   template files - you can upload, view, and delete templates.

   Once you have uploaded one or more templates, use PDF Template Settings in the
   view's configuration to select templates in any combination for leading, background,
   or trailing position. For leading and trailing templates you can select whether to
   print page headers and/or footers on the template.
