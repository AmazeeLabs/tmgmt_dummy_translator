<?php

/**
 * @file
 *  The dummy TMGMT translator.
 */

/**
 * TMGMT Plugin Controller for the dummy translator service.
 */
class TMGMTDummyPluginController extends TMGMTDefaultTranslatorPluginController {

  /**
   * {@inheritdoc}
   */
  public function requestTranslation(TMGMTJob $job) {
    // Our dummy translator will just put the language name in front of the
    // source texts.
    $translation = array();
    $items = $job->getItems();
    $langs = language_list();
    $target_language = $langs[$job->target_language];
    foreach ($items as $tjiid => $item) {
      $itemsourcedata = $item->getData();
      $fields = array_filter(tmgmt_flatten_data($itemsourcedata), '_tmgmt_filter_data');
      foreach ($fields as $fieldarray_id => $field_array) {
        $translation[$tjiid . TMGMT_ARRAY_DELIMITER . $fieldarray_id] = array(
          '#text' => $target_language->name . ': ' . $field_array['#text']
        );
      }
    }
    $job->addTranslatedData(tmgmt_unflatten_data($translation));
    $job->submitted();
    // We automatically accept the translation. If we do not want this, we can
    // comment the line below.
    $job->acceptTranslation();
  }
}
