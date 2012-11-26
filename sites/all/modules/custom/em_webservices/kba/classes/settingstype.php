<?php

class settingstype
{

  /**
   * 
   * @var accountnametype $accountname
   * @access public
   */
  public $accountname;

  /**
   * 
   * @var modetype $mode
   * @access public
   */
  public $mode;

  /**
   * 
   * @var string $ruleset
   * @access public
   */
  public $ruleset;

  /**
   * 
   * @var simulatormodetype $simulatormode
   * @access public
   */
  public $simulatormode;

  /**
   * 
   * @var attachmenttype $attachmenttype
   * @access public
   */
  public $attachmenttype;

  /**
   * 
   * @var specialfeaturetype $specialfeature
   * @access public
   */
  public $specialfeature;

  /**
   * 
   * @var internationalizationtype $internationalization
   * @access public
   */
  public $internationalization;

  /**
   * 
   * @var referenceid $referenceid
   * @access public
   */
  public $referenceid;

  /**
   * 
   * @param accountnametype $accountname
   * @param modetype $mode
   * @param string $ruleset
   * @param simulatormodetype $simulatormode
   * @param attachmenttype $attachmenttype
   * @param specialfeaturetype $specialfeature
   * @param internationalizationtype $internationalization
   * @param referenceid $referenceid
   * @access public
   */
  public function __construct($accountname, $mode, $ruleset, $simulatormode, $attachmenttype, $specialfeature, $internationalization, $referenceid)
  {
    $this->accountname = $accountname;
    $this->mode = $mode;
    $this->ruleset = $ruleset;
    $this->simulatormode = $simulatormode;
    $this->attachmenttype = $attachmenttype;
    $this->specialfeature = $specialfeature;
    $this->internationalization = $internationalization;
    $this->referenceid = $referenceid;
  }

}
