<?php

class persontype
{

  /**
   * 
   * @var string $nameprefix
   * @access public
   */
  public $nameprefix;

  /**
   * 
   * @var string $namefirst
   * @access public
   */
  public $namefirst;

  /**
   * 
   * @var string $namemiddle
   * @access public
   */
  public $namemiddle;

  /**
   * 
   * @var string $namelast
   * @access public
   */
  public $namelast;

  /**
   * 
   * @var string $namesuffix
   * @access public
   */
  public $namesuffix;

  /**
   * 
   * @var customeridtype $customerid
   * @access public
   */
  public $customerid;

  /**
   * 
   * @var emailtype $email
   * @access public
   */
  public $email;

  /**
   * 
   * @var string $ssn
   * @access public
   */
  public $ssn;

  /**
   * 
   * @var ssntype $ssntype
   * @access public
   */
  public $ssntype;

  /**
   * 
   * @var string $driverslicensenumber
   * @access public
   */
  public $driverslicensenumber;

  /**
   * 
   * @var string $driverslicensestate
   * @access public
   */
  public $driverslicensestate;

  /**
   * 
   * @var birthdatetype $birthdate
   * @access public
   */
  public $birthdate;

  /**
   * 
   * @var addresstype $address
   * @access public
   */
  public $address;

  /**
   * 
   * @var ukaddresstype $ukaddress
   * @access public
   */
  public $ukaddress;

  /**
   * 
   * @var phonenumbertype $phonenumber
   * @access public
   */
  public $phonenumber;

  /**
   * 
   * @var businesstype $business
   * @access public
   */
  public $business;

  /**
   * 
   * @var businesstype $employer
   * @access public
   */
  public $employer;

  /**
   * 
   * @var string $occupation
   * @access public
   */
  public $occupation;

  /**
   * 
   * @var riskassessmenttype $riskassessment
   * @access public
   */
  public $riskassessment;

  /**
   * 
   * @param string $nameprefix
   * @param string $namefirst
   * @param string $namemiddle
   * @param string $namelast
   * @param string $namesuffix
   * @param customeridtype $customerid
   * @param emailtype $email
   * @param string $ssn
   * @param ssntype $ssntype
   * @param string $driverslicensenumber
   * @param string $driverslicensestate
   * @param birthdatetype $birthdate
   * @param addresstype $address
   * @param ukaddresstype $ukaddress
   * @param phonenumbertype $phonenumber
   * @param businesstype $business
   * @param businesstype $employer
   * @param string $occupation
   * @param riskassessmenttype $riskassessment
   * @access public
   */
  public function __construct($nameprefix, $namefirst, $namemiddle, $namelast, $namesuffix, $customerid, $email, $ssn, $ssntype, $driverslicensenumber, $driverslicensestate, $birthdate, $address, $ukaddress, $phonenumber, $business, $employer, $occupation, $riskassessment)
  {
    $this->nameprefix = $nameprefix;
    $this->namefirst = $namefirst;
    $this->namemiddle = $namemiddle;
    $this->namelast = $namelast;
    $this->namesuffix = $namesuffix;
    $this->customerid = $customerid;
    $this->email = $email;
    $this->ssn = $ssn;
    $this->ssntype = $ssntype;
    $this->driverslicensenumber = $driverslicensenumber;
    $this->driverslicensestate = $driverslicensestate;
    $this->birthdate = $birthdate;
    $this->address = $address;
    $this->ukaddress = $ukaddress;
    $this->phonenumber = $phonenumber;
    $this->business = $business;
    $this->employer = $employer;
    $this->occupation = $occupation;
    $this->riskassessment = $riskassessment;
  }

}
