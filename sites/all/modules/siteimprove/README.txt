# Siteimprove Plugin

## Introduction

The Siteimprove plugin bridges the gap between Drupal and the Siteimprove
Intelligence Platform. You are now able to put your Siteimprove results to use
where they are most valuable – during your content creationand editing
process. With analytics and content insights always at hand, contributors
can test, fix, and optimize their work continuously. Once the detected issues
have been assessed, you can directly re-recheck the relevant page and see if
further actions are needed. Delivering a superior digital experience has never
been more efficient and convenient.

## Installation and configuration

Siteimprove Plugin can be installed like any other Drupal module.
Place it in the modules directory for your site and enable it
on the `admin/modules` page.

Visit the Siteimprove Plugin settings page and regenerate auth token
if you need it.

If you are using a separate edit or backend domain, can you configure your
frontend domain in the settings page, and Siteimprove will always use this
in the overlay.

## Developer

If you want to rewrite the frontend domain in custom code, then implement
hook_siteimprove_frontend_url_alter(&$rewritten_url, $original_url).

## Frequently Asked Questions

Who can use this plugin?
The plugin requires a Siteimprove subscription to be used.
Signup for a [FreeTrial](https://siteimprove.com/account/create “Free trial”)
to test it out.

Where can I see the overlay?
The overlay is visible when editing a page.

I don't see the overlay, whats wrong?
Did you remember to turn off your adblocker? Some adblockers does not like
our iframe overlay.
