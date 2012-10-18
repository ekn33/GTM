<?php

/**
 * @file
 * Admin callbacks for the Google Tag Manager module.
 */

/**
 * Implementation of hook_admin_settings()
 */
function gtm_admin_settings_form(&$form_state) {

  $form['gtm'] = array(
    '#type' => 'textarea',
    '#title' => t('Google Tag Manager Snippet'),
    '#default_value' => variable_get('gtm', ''),
    '#size' => 20,
    '#rows' => 7,
    '#required' => TRUE,
    '#description' => t('If you do not already have a Google Tag Manager Account, create here one: !link', array('!link' => l('https://www.google.com/tagmanager', 'https://www.google.com/tagmanager'))),
  );

  // Render the role overview.
  $result = db_query('SELECT * FROM {role} ORDER BY name');

  $form['roles'] = array(
        '#type' => 'fieldset',
        '#title' => t('User Role Tracking'),
        '#collapsible' => TRUE,
        '#description' => t('Define what user roles should be tracked by Google.')
  );

  while ($role = db_fetch_object($result)) {
    // can't use empty spaces in varname
    $role_varname = $string = str_replace(' ', '_', $role->name);
    $form['roles']["gtm_track_{$role_varname}"] = array(
      '#type' => 'checkbox',
      '#title' => t($role->name),
      '#default_value' => variable_get("gtm_track_{$role_varname}", FALSE),
    );
  }

  return system_settings_form($form);
}
