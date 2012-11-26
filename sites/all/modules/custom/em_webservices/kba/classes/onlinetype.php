<?php

class onlinetype
{

  /**
   * 
   * @var credentialtype $credential
   * @access public
   */
  public $credential;

  /**
   * 
   * @param credentialtype $credential
   * @access public
   */
  public function __construct($credential)
  {
    $this->credential = $credential;
  }

}
