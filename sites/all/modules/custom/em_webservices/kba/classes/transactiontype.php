<?php

class transactiontype
{

  /**
   * 
   * @var purchasetype $purchase
   * @access public
   */
  public $purchase;

  /**
   * 
   * @var accountverificationtype $accountverification
   * @access public
   */
  public $accountverification;

  /**
   * 
   * @param purchasetype $purchase
   * @param accountverificationtype $accountverification
   * @access public
   */
  public function __construct($purchase, $accountverification)
  {
    $this->purchase = $purchase;
    $this->accountverification = $accountverification;
  }

}
