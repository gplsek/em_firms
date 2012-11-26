<?php

class transactionauthenticationcheck
{

  /**
   * 
   * @var settings $settings
   * @access public
   */
  public $settings;

  /**
   * 
   * @var credentialtype $credential
   * @access public
   */
  public $credential;

  /**
   * 
   * @var accounttype $account
   * @access public
   */
  public $account;

  /**
   * 
   * @param settings $settings
   * @param credentialtype $credential
   * @param accounttype $account
   * @access public
   */
  public function __construct($settings, $credential, $account)
  {
    $this->settings = $settings;
    $this->credential = $credential;
    $this->account = $account;
  }

}
