<?php

class accountoriginationtype
{

  /**
   * 
   * @var accountcategorytype $accountcategory
   * @access public
   */
  public $accountcategory;

  /**
   * 
   * @var securityquestiontype $securityquestion
   * @access public
   */
  public $securityquestion;

  /**
   * 
   * @var boolean $voiceenrollment
   * @access public
   */
  public $voiceenrollment;

  /**
   * 
   * @var accounttype $account
   * @access public
   */
  public $account;

  /**
   * 
   * @param accountcategorytype $accountcategory
   * @param securityquestiontype $securityquestion
   * @param boolean $voiceenrollment
   * @param accounttype $account
   * @access public
   */
  public function __construct($accountcategory, $securityquestion, $voiceenrollment, $account)
  {
    $this->accountcategory = $accountcategory;
    $this->securityquestion = $securityquestion;
    $this->voiceenrollment = $voiceenrollment;
    $this->account = $account;
  }

}
