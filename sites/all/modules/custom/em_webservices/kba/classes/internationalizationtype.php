<?php

class internationalizationtype
{

  /**
   * 
   * @var languagetype $language
   * @access public
   */
  public $language;

  /**
   * 
   * @var languagevenuetype $languagevenue
   * @access public
   */
  public $languagevenue;

  /**
   * 
   * @param languagetype $language
   * @param languagevenuetype $languagevenue
   * @access public
   */
  public function __construct($language, $languagevenue)
  {
    $this->language = $language;
    $this->languagevenue = $languagevenue;
  }

}
