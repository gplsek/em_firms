<?php

class accountverificationtype
{

  /**
   * 
   * @var accountmaintenancetype $accountmaintenance
   * @access public
   */
  public $accountmaintenance;

  /**
   * 
   * @var accountactivitytype $accountactivity
   * @access public
   */
  public $accountactivity;

  /**
   * 
   * @var accountoriginationtype $accountorigination
   * @access public
   */
  public $accountorigination;

  /**
   * 
   * @var venuetype $venue
   * @access public
   */
  public $venue;

  /**
   * 
   * @var transactiondatetype $activitydate
   * @access public
   */
  public $activitydate;

  /**
   * 
   * @var riskassessmenttype $riskassessment
   * @access public
   */
  public $riskassessment;

  /**
   * 
   * @param accountmaintenancetype $accountmaintenance
   * @param accountactivitytype $accountactivity
   * @param accountoriginationtype $accountorigination
   * @param venuetype $venue
   * @param transactiondatetype $activitydate
   * @param riskassessmenttype $riskassessment
   * @access public
   */
  public function __construct($accountmaintenance, $accountactivity, $accountorigination, $venue, $activitydate, $riskassessment)
  {
    $this->accountmaintenance = $accountmaintenance;
    $this->accountactivity = $accountactivity;
    $this->accountorigination = $accountorigination;
    $this->venue = $venue;
    $this->activitydate = $activitydate;
    $this->riskassessment = $riskassessment;
  }

}
