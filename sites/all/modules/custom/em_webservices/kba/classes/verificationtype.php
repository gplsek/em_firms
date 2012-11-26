<?php

class verificationtype
{

  /**
   * 
   * @var venuetype $venue
   * @access public
   */
  public $venue;

  /**
   * 
   * @param venuetype $venue
   * @access public
   */
  public function __construct($venue)
  {
    $this->venue = $venue;
  }

}
