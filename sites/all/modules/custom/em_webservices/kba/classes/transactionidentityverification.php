<?php

class transactionidentityverification
{

  /**
   * 
   * @var identityverificationsettingstype $settings
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
   * @var transactiontype $transaction
   * @access public
   */
  public $transaction;

  /**
   * 
   * @var identityassertiontype $identityassertion
   * @access public
   */
  public $identityassertion;

  /**
   * 
   * @param identityverificationsettingstype $settings
   * @param persontype $person
   * @param transactiontype $transaction
   * @param identityassertiontype $identityassertion
   * @access public
   */
  public function __construct($settings, $person, $transaction, $identityassertion)
  {
    $this->settings = $settings;
    $this->person = $person;
    $this->transaction = $transaction;
    $this->identityassertion = $identityassertion;
  }

}
