<?php
ini_set('display_errors',1);
error_reporting(E_ALL);
$flickr_url = "https://api.flickr.com/services/rest/?&method=flickr.people.getPublicPhotos&api_key=24ad194cceb24285045f026dff301622&user_id=spcouta&per_page=5&sort=date-taken-desc&format=json&nojsoncallback=1";

      $response = file_get_contents("https://api.flickr.com/services/rest/?&method=flickr.people.getPublicPhotos&api_key=24ad194cceb24285045f026dff301622&user_id=spcouta&per_page=5&sort=date-taken-desc&format=json&nojsoncallback=1");
    $results_flickr = json_decode($response);
      //FLICKR RESULTS

       $block_content = "<div class='col-sm-12' id='flickr'>";
       //if there are photos
       if ($results_flickr->photos->total != 0) {
       $flickr_count = 0;
       $photoarray = array();
      foreach($results_flickr->photo as $photo) {
        $flickr_count++;
        $photoid = $photo->id;
        $phototitle = $photo->title;
        $photourl = file_get_contents("https://api.flickr.com/services/rest/?&method=flickr.photos.getSizes&api_key=24ad194cceb24285045f026dff301622&photo_id=" . $photoid . "&format=json&nojsoncallback=1");
        $photojson = json_decode($photourl);
        $thumb = NULL;
        foreach($photojson->sizes->size as $size) {
          if ($size->label == 'Medium 800') {
            $thumb = $size->source;
            $photolink = $size->url;
            $photoarray[] = $thumb;
          } else if ($size->label == 'Medium' && $thumb == NULL) {
            $thumb = $size->source;
            $photolink = $size->url;
            $photoarray[] = $thumb;
          }
        }
      }
          $i = rand(0, count($photoarray)-1);
          $block_content .= "<img src='" . $photoarray[$i] . "' alt='Flickr Image' />";
          $block_content .= "</div>";
      }
      else {
        $block_content = "";
      }
      $block_content .= "<p class='clearfix pull-right'>Powered by <a href='https://www.flickr.com/photos/spcouta'>Flickr</a></p>";

    return $block_content;
    ?>