<?php

class callcentertype
{

  /**
   * 
   * @var string $callerphonenumber
   * @access public
   */
  public $callerphonenumber;

  /**
   * 
   * @var credentialmethodtype $credentialmethod
   * @access public
   */
  public $credentialmethod;

  /**
   * 
   * @var string $callerid
   * @access public
   */
  public $callerid;

  /**
   * 
   * @param string $callerphonenumber
   * @param credentialmethodtype $credentialmethod
   * @param string $callerid
   * @access public
   */
  public function __construct($callerphonenumber, $credentialmethod, $callerid)
  {
    $this->callerphonenumber = $callerphonenumber;
    $this->credentialmethod = $credentialmethod;
    $this->callerid = $callerid;
  }

}
