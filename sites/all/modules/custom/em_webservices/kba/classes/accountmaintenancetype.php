<?php

class accountmaintenancetype
{

  /**
   * 
   * @var accountcategorytype $accountcategory
   * @access public
   */
  public $accountcategory;

  /**
   * 
   * @var accountmaintenancecategorytype $accountmaintenancecategory
   * @access public
   */
  public $accountmaintenancecategory;

  /**
   * 
   * @var string $maintenancedetail
   * @access public
   */
  public $maintenancedetail;

  /**
   * 
   * @var accounttype $account
   * @access public
   */
  public $account;

  /**
   * 
   * @var complexdetailtype $data
   * @access public
   */
  public $data;

  /**
   * 
   * @param accountcategorytype $accountcategory
   * @param accountmaintenancecategorytype $accountmaintenancecategory
   * @param string $maintenancedetail
   * @param accounttype $account
   * @param complexdetailtype $data
   * @access public
   */
  public function __construct($accountcategory, $accountmaintenancecategory, $maintenancedetail, $account, $data)
  {
    $this->accountcategory = $accountcategory;
    $this->accountmaintenancecategory = $accountmaintenancecategory;
    $this->maintenancedetail = $maintenancedetail;
    $this->account = $account;
    $this->data = $data;
  }

}
