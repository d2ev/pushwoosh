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
    '#title' => t('Enable pushwoosh push notifications for https/https websites.'),
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
    <li>For pushwoosh account settings follow instructions 
    here - 
    http://docs.pushwoosh.com/docs/chrome-web-push,
    http://docs.pushwoosh.com/docs/firefox-web-push,
    http://docs.pushwoosh.com/docs/safari-website-notifications</li></ul>',
  );

  $form['pushwoosh_https']['pushwoosh_manifest'] = array(
    '#title' => t('manifest.json'),
    '#type' => 'textarea',
    '#description' => t('Make sure the following URL is publicly accessible:https://yoursite.com/manifest.json and file is writable.'),
    '#element_validate' => array('pushwoosh_validate'),
    '#default_value' => variable_get('pushwoosh_manifest') ? variable_get('pushwoosh_manifest') : '{
  "name": "Name of your website",
  "short_name": "Name of your website",
  "gcm_sender_id": "Your Google Project Number is usually a 12-digit number",
  "display": "standalone",
  "gcm_user_visible_only": true
}',
  );

  $form['pushwoosh_https']['pushwoosh_loglevel'] = array(
    '#type' => 'select',
    '#title' => t('logLevel'),
    '#options' => drupal_map_assoc(array('info', 'debug')),
    '#default_value' => variable_get('pushwoosh_loglevel', 'info'),
    '#element_validate' => array('pushwoosh_validate'),
  );
  $form['pushwoosh_https']['pushwoosh_swpid'] = array(
    '#type' => 'textfield',
    '#title' => t('safariWebsitePushID'),
    '#default_value' => variable_get('pushwoosh_swpid', 'web.com.example.domain'),
    '#size' => 60,
    '#maxlength' => 60,
    '#element_validate' => array('pushwoosh_validate'),
  );
  $form['pushwoosh_https']['pushwoosh_dnt'] = array(
    '#type' => 'textfield',
    '#title' => t('defaultNotificationTitle'),
    '#default_value' => variable_get('pushwoosh_dnt', 'Pushwoosh Demo'),
    '#size' => 60,
    '#maxlength' => 60,
    '#element_validate' => array('pushwoosh_validate'),
  );
  $form['pushwoosh_https']['pushwoosh_dni'] = array(
    '#type' => 'textfield',
    '#title' => t('defaultNotificationImage'),
    '#default_value' => variable_get('pushwoosh_dni', 'https://cp.pushwoosh.com/img/logo-medium.png'),
    '#size' => 60,
    '#maxlength' => 60,
    '#element_validate' => array('pushwoosh_validate'),
  );

  // HTTP settings.
  $form['pushwoosh_http']['pushwoosh_http'] = array(
    '#markup' => '<ul><li>Enable settings push notifications for Chrome and Firefox 
    http websites.</li><li> For pushwoosh account settings for http 
    follow the instruction here - http://docs.pushwoosh.com/docs/chrome-web-push-for-http-websites</li></ul>',
  );
  
  // Tag settings.
  $form['pushwoosh_tags'] = array(
    '#title' => t('Tags'),
    '#type' => 'textarea',
    '#description' => t('Set tags for the user. Enter JSON object key as tag 
    name and value can be string or callback (callback should end with _get 
    string). example: {"Tag Name 1": "mymodule_name_get",  "Tag Name 2": "mymodule_dob_get",  "Tag Name 3": "www.example.com"}'),
    '#default_value' => variable_get('pushwoosh_tags'),
  );

  $form['#submit'][] = 'pushwoosh_admin_submit';

  return system_settings_form($form);
}

function pushwoosh_validate($element, &$form_state, $form) {
  if ($form_state['values']['pushwoosh_protocol'] == ' HTTPS' &&
    empty($element['#value'])
  ) {
    form_error($element, t('This field is required.'));
  }
}

/**
 * @param $form
 * @param $form_state
 */
function pushwoosh_admin_submit($form, &$form_state) {
  // Create or save manifest.json file.
  global $base_url;
  $manifest = $form_state['values']['pushwoosh_manifest'];
  file_put_contents(DRUPAL_ROOT.'/manifest.json', $manifest);
}
