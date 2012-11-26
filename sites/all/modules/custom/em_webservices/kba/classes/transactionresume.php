<?php

class transactionresume
{

  /**
   * 
   * @var resumesettingstype $settings
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
   * @param resumesettingstype $settings
   * @param accounttype $account
   * @access public
   */
  public function __construct($settings, $account)
  {
    $this->settings = $settings;
    $this->account = $account;
  }

}
