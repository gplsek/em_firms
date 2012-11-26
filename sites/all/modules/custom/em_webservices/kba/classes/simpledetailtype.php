<?php

class simpledetailtype
{

  /**
   * 
   * @var string $text
   * @access public
   */
  public $text;

  /**
   * 
   * @param string $text
   * @access public
   */
  public function __construct($text)
  {
    $this->text = $text;
  }

}
