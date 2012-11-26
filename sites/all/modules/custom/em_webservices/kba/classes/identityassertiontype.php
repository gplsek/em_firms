<?php

class identityassertiontype
{

  /**
   * 
   * @var complexdetailtype $data
   * @access public
   */
  public $data;

  /**
   * 
   * @var transactiontype $transaction
   * @access public
   */
  public $transaction;

  /**
   * 
   * @param complexdetailtype $data
   * @param transactiontype $transaction
   * @access public
   */
  public function __construct($data, $transaction)
  {
    $this->data = $data;
    $this->transaction = $transaction;
  }

}
