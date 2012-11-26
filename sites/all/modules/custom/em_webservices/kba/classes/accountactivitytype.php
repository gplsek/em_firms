<?php

class accountactivitytype
{

  /**
   * 
   * @var accounttype $account
   * @access public
   */
  public $account;

  /**
   * 
   * @var producttype $accounttransaction
   * @access public
   */
  public $accounttransaction;

  /**
   * 
   * @var float $totalamount
   * @access public
   */
  public $totalamount;

  /**
   * 
   * @var float $beginningbalance
   * @access public
   */
  public $beginningbalance;

  /**
   * 
   * @var float $endingbalance
   * @access public
   */
  public $endingbalance;

  /**
   * 
   * @param accounttype $account
   * @param producttype $accounttransaction
   * @param float $totalamount
   * @param float $beginningbalance
   * @param float $endingbalance
   * @access public
   */
  public function __construct($account, $accounttransaction, $totalamount, $beginningbalance, $endingbalance)
  {
    $this->account = $account;
    $this->accounttransaction = $accounttransaction;
    $this->totalamount = $totalamount;
    $this->beginningbalance = $beginningbalance;
    $this->endingbalance = $endingbalance;
  }

}
