<?php

class netviewtype
{

  /**
   * 
   * @var netviewformtype $netviewform
   * @access public
   */
  public $netviewform;

  /**
   * 
   * @param netviewformtype $netviewform
   * @access public
   */
  public function __construct($netviewform)
  {
    $this->netviewform = $netviewform;
  }

}
