<?php

class assertionresponse
{

  /**
   * 
   * @var transactionstatustype $assertionstatus
   * @access public
   */
  public $assertionstatus;

  /**
   * 
   * @var informationtype $information
   * @access public
   */
  public $information;

  /**
   * 
   * @param transactionstatustype $assertionstatus
   * @param informationtype $information
   * @access public
   */
  public function __construct($assertionstatus, $information)
  {
    $this->assertionstatus = $assertionstatus;
    $this->information = $information;
  }

}
