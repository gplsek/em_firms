<?php

class accounttype
{

  /**
   * 
   * @var accountnumbertype $accountnumber
   * @access public
   */
  public $accountnumber;

  /**
   * 
   * @var accounttransactionidtype $accounttransactionid
   * @access public
   */
  public $accounttransactionid;

  /**
   * 
   * @var accountnametype $accountname
   * @access public
   */
  public $accountname;

  /**
   * 
   * @var customeridtype $customerid
   * @access public
   */
  public $customerid;

  /**
   * 
   * @param accountnumbertype $accountnumber
   * @param accounttransactionidtype $accounttransactionid
   * @param accountnametype $accountname
   * @param customeridtype $customerid
   * @access public
   */
  public function __construct($accountnumber, $accounttransactionid, $accountname, $customerid)
  {
    $this->accountnumber = $accountnumber;
    $this->accounttransactionid = $accounttransactionid;
    $this->accountname = $accountname;
    $this->customerid = $customerid;
  }

}
