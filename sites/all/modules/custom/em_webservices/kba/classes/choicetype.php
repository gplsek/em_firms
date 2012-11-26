<?php

class choicetype
{

  /**
   * 
   * @var int $choiceid
   * @access public
   */
  public $choiceid;

  /**
   * 
   * @var texttype $text
   * @access public
   */
  public $text;

  /**
   * 
   * @param int $choiceid
   * @param texttype $text
   * @access public
   */
  public function __construct($choiceid, $text)
  {
    $this->choiceid = $choiceid;
    $this->text = $text;
  }

}
