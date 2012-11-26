<?php

class choicestype
{

  /**
   * 
   * @var int $choiceid
   * @access public
   */
  public $choiceid;

  /**
   * 
   * @param int $choiceid
   * @access public
   */
  public function __construct($choiceid)
  {
    $this->choiceid = $choiceid;
  }

}
