<?php

# if the request was not SSL
if (empty($_SERVER[ "HTTPS" ]))
{
  # and if there is a script URI to redirect to
  if( !empty( $_SERVER[ "SCRIPT_URI" ] ))
  {
    # forward them to the SSL version of the script they requested
    $new_url = str_ireplace( "http://", "https://", $_SERVER[ "SCRIPT_URI" ] );
    if (!empty($_SERVER["REDIRECT_QUERY_STRING"])) $new_url .= "?" . $_SERVER['REDIRECT_QUERY_STRING'];
    header( "Location: ${new_url}" );
    exit;
  }
}

# if we didn't redirect them, show the normal 403 error page
#include "/opt/libwebfs/web-libweb-nm-test/library-test.uta.edu/node/533";

?>