<?php

class pointofsale
{

  /**
   * 
   * @var credentialmethodtype $credentialmethod
   * @access public
   */
  public $credentialmethod;

  /**
   * 
   * @var string $merchantzipcode
   * @access public
   */
  public $merchantzipcode;

  /**
   * 
   * @param credentialmethodtype $credentialmethod
   * @param string $merchantzipcode
   * @access public
   */
  public function __construct($credentialmethod, $merchantzipcode)
  {
    $this->credentialmethod = $credentialmethod;
    $this->merchantzipcode = $merchantzipcode;
  }

}
