<?php

class dispositionsettingstype
{

  /**
   * 
   * @var transactionidtype $transactionid
   * @access public
   */
  public $transactionid;

  /**
   * 
   * @param transactionidtype $transactionid
   * @access public
   */
  public function __construct($transactionid)
  {
    $this->transactionid = $transactionid;
  }

}
