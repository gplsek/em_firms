<?php

class addresstype
{

  /**
   * 
   * @var string $addressstreet1
   * @access public
   */
  public $addressstreet1;

  /**
   * 
   * @var string $addressstreet2
   * @access public
   */
  public $addressstreet2;

  /**
   * 
   * @var string $suite
   * @access public
   */
  public $suite;

  /**
   * 
   * @var string $addresscity
   * @access public
   */
  public $addresscity;

  /**
   * 
   * @var string $addressstate
   * @access public
   */
  public $addressstate;

  /**
   * 
   * @var string $addresszip
   * @access public
   */
  public $addresszip;

  /**
   * 
   * @var string $addresszipplus4
   * @access public
   */
  public $addresszipplus4;

  /**
   * 
   * @var string $addresscountry
   * @access public
   */
  public $addresscountry;

  /**
   * 
   * @var addresscontexttype $addresscontext
   * @access public
   */
  public $addresscontext;

  /**
   * 
   * @var float $addressyearsat
   * @access public
   */
  public $addressyearsat;

  /**
   * 
   * @var date $occupationstartdate
   * @access public
   */
  public $occupationstartdate;

  /**
   * 
   * @param string $addressstreet1
   * @param string $addressstreet2
   * @param string $suite
   * @param string $addresscity
   * @param string $addressstate
   * @param string $addresszip
   * @param string $addresszipplus4
   * @param string $addresscountry
   * @param addresscontexttype $addresscontext
   * @param float $addressyearsat
   * @param date $occupationstartdate
   * @access public
   */
  public function __construct($addressstreet1, $addressstreet2, $suite, $addresscity, $addressstate, $addresszip, $addresszipplus4, $addresscountry, $addresscontext, $addressyearsat, $occupationstartdate)
  {
    $this->addressstreet1 = $addressstreet1;
    $this->addressstreet2 = $addressstreet2;
    $this->suite = $suite;
    $this->addresscity = $addresscity;
    $this->addressstate = $addressstate;
    $this->addresszip = $addresszip;
    $this->addresszipplus4 = $addresszipplus4;
    $this->addresscountry = $addresscountry;
    $this->addresscontext = $addresscontext;
    $this->addressyearsat = $addressyearsat;
    $this->occupationstartdate = $occupationstartdate;
  }

}
