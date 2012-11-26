<?php

class texttype
{

  /**
   * 
   * @var languagetype $language
   * @access public
   */
  public $language;

  /**
   * 
   * @var string $statement
   * @access public
   */
  public $statement;

  /**
   * 
   * @param languagetype $language
   * @param string $statement
   * @access public
   */
  public function __construct($language, $statement)
  {
    $this->language = $language;
    $this->statement = $statement;
  }

}
