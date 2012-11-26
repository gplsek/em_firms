<?php

class transactionstatustype
{

  /**
   * 
   * @var transactionidtype $transactionid
   * @access public
   */
  public $transactionid;

  /**
   * 
   * @var transactionidtype $transactionrequestid
   * @access public
   */
  public $transactionrequestid;

  /**
   * 
   * @var string $accountstransactionid
   * @access public
   */
  public $accountstransactionid;

  /**
   * 
   * @var referenceid $referenceid
   * @access public
   */
  public $referenceid;

  /**
   * 
   * @var transactionresulttype $transactionresult
   * @access public
   */
  public $transactionresult;

  /**
   * 
   * @var riskassessmenttype $riskassessment
   * @access public
   */
  public $riskassessment;

  /**
   * 
   * @var specialfeaturetype $specialfeature
   * @access public
   */
  public $specialfeature;

  /**
   * 
   * @param transactionidtype $transactionid
   * @param transactionidtype $transactionrequestid
   * @param string $accountstransactionid
   * @param referenceid $referenceid
   * @param transactionresulttype $transactionresult
   * @param riskassessmenttype $riskassessment
   * @param specialfeaturetype $specialfeature
   * @access public
   */
  public function __construct($transactionid, $transactionrequestid, $accountstransactionid, $referenceid, $transactionresult, $riskassessment, $specialfeature)
  {
    $this->transactionid = $transactionid;
    $this->transactionrequestid = $transactionrequestid;
    $this->accountstransactionid = $accountstransactionid;
    $this->referenceid = $referenceid;
    $this->transactionresult = $transactionresult;
    $this->riskassessment = $riskassessment;
    $this->specialfeature = $specialfeature;
  }

}
