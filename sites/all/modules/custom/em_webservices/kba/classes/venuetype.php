<?php

class venuetype
{

  /**
   * 
   * @var onlinetype $online
   * @access public
   */
  public $online;

  /**
   * 
   * @var callcentertype $callcenter
   * @access public
   */
  public $callcenter;

  /**
   * 
   * @var batchtype $batch
   * @access public
   */
  public $batch;

  /**
   * 
   * @var netviewtype $netview
   * @access public
   */
  public $netview;

  /**
   * 
   * @var pointofsale $pointofsale
   * @access public
   */
  public $pointofsale;

  /**
   * 
   * @var customerservicetype $customerservice
   * @access public
   */
  public $customerservice;

  /**
   * 
   * @var ivrtype $ivr
   * @access public
   */
  public $ivr;

  /**
   * 
   * @param onlinetype $online
   * @param callcentertype $callcenter
   * @param batchtype $batch
   * @param netviewtype $netview
   * @param pointofsale $pointofsale
   * @param customerservicetype $customerservice
   * @param ivrtype $ivr
   * @access public
   */
  public function __construct($online, $callcenter, $batch, $netview, $pointofsale, $customerservice, $ivr)
  {
    $this->online = $online;
    $this->callcenter = $callcenter;
    $this->batch = $batch;
    $this->netview = $netview;
    $this->pointofsale = $pointofsale;
    $this->customerservice = $customerservice;
    $this->ivr = $ivr;
  }

}
