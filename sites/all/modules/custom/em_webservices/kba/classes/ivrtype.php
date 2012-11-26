<?php

class ivrtype
{

  /**
   * 
   * @var credentialmethodtype $credentialmethod
   * @access public
   */
  public $credentialmethod;

  /**
   * 
   * @param credentialmethodtype $credentialmethod
   * @access public
   */
  public function __construct($credentialmethod)
  {
    $this->credentialmethod = $credentialmethod;
  }

}
