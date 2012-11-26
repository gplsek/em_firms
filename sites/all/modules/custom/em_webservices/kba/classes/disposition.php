<?php

class disposition
{

  /**
   * 
   * @var dispositionsettingstype $settings
   * @access public
   */
  public $settings;

  /**
   * 
   * @var accounttype $account
   * @access public
   */
  public $account;

  /**
   * 
   * @var fraudcategorytype $fraudcategory
   * @access public
   */
  public $fraudcategory;

  /**
   * 
   * @var dispositionstatustype $dispositionstatus
   * @access public
   */
  public $dispositionstatus;

  /**
   * 
   * @var dispositiondatetype $dispositiondate
   * @access public
   */
  public $dispositiondate;

  /**
   * 
   * @param dispositionsettingstype $settings
   * @param accounttype $account
   * @param fraudcategorytype $fraudcategory
   * @param dispositionstatustype $dispositionstatus
   * @param dispositiondatetype $dispositiondate
   * @access public
   */
  public function __construct($settings, $account, $fraudcategory, $dispositionstatus, $dispositiondate)
  {
    $this->settings = $settings;
    $this->account = $account;
    $this->fraudcategory = $fraudcategory;
    $this->dispositionstatus = $dispositionstatus;
    $this->dispositiondate = $dispositiondate;
  }

}
