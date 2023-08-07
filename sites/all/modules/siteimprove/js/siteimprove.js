/**
 * @file
 * Contains the Siteimprove Plugin methods.
 */

(function ($) {

  'use strict';

  var siteimprove = {
    input: function () {
      this.url = Drupal.settings.siteimprove.input.url;
      this.method = 'input';
      this.common();
    },
    domain: function () {
      this.url = Drupal.settings.siteimprove.domain.url;
      this.method = 'domain';
      this.common();
    },
    clear: function () {
      this.method = 'clear';
      var _si = window._si || [];
      _si.push([this.method, function() { }, Drupal.settings.siteimprove.token]);
    },
    recheck: function () {
      this.url = Drupal.settings.siteimprove.recheck.url;
      this.method = 'recheck';
      this.common();
    },
    recrawl: function () {
      this.url = Drupal.settings.siteimprove.recrawl.url;
      this.method = 'recrawl';
      this.common();
    },
    common: function () {
      var _si = window._si || [];
      _si.push([this.method, this.url, Drupal.settings.siteimprove.token]);
    },
    events: {
      recheck: function () {
        $('.recheck-button').click(function () {
          siteimprove.recheck();
          $(this).attr('disabled', true);
          $(this).addClass('form-button-disabled');
          return false;
        });
      }
    }
  };

  Drupal.behaviors.siteimprove = {
    attach: function (context, settings) {

      // If exist recheck, call recheck Siteimprove method.
      if (typeof settings.siteimprove.recheck !== 'undefined') {
        if (settings.siteimprove.recheck.auto) {
          siteimprove.recheck();
        }
        siteimprove.events.recheck();
      }

      // If exist input, call input Siteimprove method.
      if (typeof settings.siteimprove.input !== 'undefined') {
        if (settings.siteimprove.input.auto) {
          siteimprove.input();
        }
      }

      // If exist domain, call domain Siteimprove method.
      if (typeof settings.siteimprove.domain !== 'undefined') {
        if (settings.siteimprove.domain.auto) {
          siteimprove.domain();
        }
      }

      // If exist clear, call clear Siteimprove method.
      if (typeof settings.siteimprove.clear !== 'undefined') {
        if (settings.siteimprove.clear.auto) {
          siteimprove.clear();
        }
      }

      // If exist recrawl, call input Siteimprove method.
      if (typeof settings.siteimprove.recrawl !== 'undefined') {
        if (settings.siteimprove.recrawl.auto) {
          siteimprove.recrawl();
        }
      }
    }
  };

})(jQuery);
