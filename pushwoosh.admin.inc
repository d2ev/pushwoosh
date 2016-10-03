<?php
/**
 * @file
 * Administrative callbacks for pushwoosh.
 */

/**
 * Form builder. Configure pushwoosh.
 */
function pushwoosh_admin_settings() {
  $form['pushwoosh_application_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Pushwoosh Application Code'),
    '#default_value' => variable_get('pushwoosh_application_code'),
    '#size' => 60,
    '#maxlength' => 60,
    '#required' => TRUE,
  );
  $form['pushwoosh_protocol'] = array(
    '#type' => 'radios',
    '#options' => drupal_map_assoc(array('HTTPS', 'HTTP')),
    '#title' => t('Enable pushwoosh push notifications for Chrome and Firefox
     https/https websites.'),
    '#default_value' => variable_get('pushwoosh_protocol'),
  );

  $form['pushwoosh_https'] = array(
    '#type' => 'container',
    '#states' => array(
      'visible' => array(
        ':input[name="pushwoosh_protocol"]' => array('value' => 'HTTPS'),
      ),
    ),
  );
  $form['pushwoosh_http'] = array(
    '#type' => 'container',
    '#states' => array(
      'visible' => array(
        ':input[name="pushwoosh_protocol"]' => array('value' => 'HTTP'),
      ),
    ),
  );
  // HTTPS settings.
  $form['pushwoosh_https']['pushwoosh_https'] = array(
    '#markup' => '<ul><li>It will not work with self-signed certificates 
    (https/ssl). You should get SSL certificate signed by trusted Authority.</li>
    <li>Push notifications don\'t work in "Incognito" mode. </li>
    <li>For pushwoosh account settings for https follow the below instructions 
    here - 
    http://docs.pushwoosh.com/docs/chrome-web-push
    http://docs.pushwoosh.com/docs/firefox-web-push</li></ul>',
  );

  // HTTP settings.
  $form['pushwoosh_http']['pushwoosh_http'] = array(
    '#markup' => '<ul><li>Enable settings push notifications for Chrome and Firefox 
    http websites.</li><li> For pushwoosh account settings for http 
    follow the instruction here - http://docs.pushwoosh.com/docs/chrome-web-push-for-http-websites</li></ul>',
  );

  return system_settings_form($form);
}
