<?php

class purchasetype
{

  /**
   * 
   * @var order $order
   * @access public
   */
  public $order;

  /**
   * 
   * @var paymentmethod $paymentmethod
   * @access public
   */
  public $paymentmethod;

  /**
   * 
   * @var shippingtype $shipping
   * @access public
   */
  public $shipping;

  /**
   * 
   * @var accounttype $account
   * @access public
   */
  public $account;

  /**
   * 
   * @var venuetype $venue
   * @access public
   */
  public $venue;

  /**
   * 
   * @var transactiondatetype $transactiondate
   * @access public
   */
  public $transactiondate;

  /**
   * 
   * @var riskassessmenttype $riskassessment
   * @access public
   */
  public $riskassessment;

  /**
   * 
   * @param order $order
   * @param paymentmethod $paymentmethod
   * @param shippingtype $shipping
   * @param accounttype $account
   * @param venuetype $venue
   * @param transactiondatetype $transactiondate
   * @param riskassessmenttype $riskassessment
   * @access public
   */
  public function __construct($order, $paymentmethod, $shipping, $account, $venue, $transactiondate, $riskassessment)
  {
    $this->order = $order;
    $this->paymentmethod = $paymentmethod;
    $this->shipping = $shipping;
    $this->account = $account;
    $this->venue = $venue;
    $this->transactiondate = $transactiondate;
    $this->riskassessment = $riskassessment;
  }

}
