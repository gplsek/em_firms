<?php

class assertion
{

  /**
   * 
   * @var settingstype $settings
   * @access public
   */
  public $settings;

  /**
   * 
   * @var persontype $person
   * @access public
   */
  public $person;

  /**
   * 
   * @var accounttype $account
   * @access public
   */
  public $account;

  /**
   * 
   * @var identityassertiontype $identityassertion
   * @access public
   */
  public $identityassertion;

  /**
   * 
   * @param settingstype $settings
   * @param persontype $person
   * @param accounttype $account
   * @param identityassertiontype $identityassertion
   * @access public
   */
  public function __construct($settings, $person, $account, $identityassertion)
  {
    $this->settings = $settings;
    $this->person = $person;
    $this->account = $account;
    $this->identityassertion = $identityassertion;
  }

}
