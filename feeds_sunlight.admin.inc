<?php

/**
 * @file
 * Administrative menu callbacks, form callbacks and helpers.
 */

//------------------------------------------------------------------------------
// Menu callbacks

/**
 * Form builder; Sunlight API settings form.
 */
function feeds_sunlight_admin_form($form, &$form_state) {

  $form['feeds_sunlight_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Sunlight Labs API key'),
    '#default_value' => variable_get('feeds_sunlight_api_key', NULL),
  );

  return system_settings_form($form);
}
