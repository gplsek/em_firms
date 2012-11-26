<?php

class businesstype
{

  /**
   * 
   * @var string $companyname
   * @access public
   */
  public $companyname;

  /**
   * 
   * @var string $fein
   * @access public
   */
  public $fein;

  /**
   * 
   * @var addresstype $address
   * @access public
   */
  public $address;

  /**
   * 
   * @var phonenumbertype $phonenumber
   * @access public
   */
  public $phonenumber;

  /**
   * 
   * @var string $title
   * @access public
   */
  public $title;

  /**
   * 
   * @var date $startdate
   * @access public
   */
  public $startdate;

  /**
   * 
   * @var date $enddate
   * @access public
   */
  public $enddate;

  /**
   * 
   * @param string $companyname
   * @param string $fein
   * @param addresstype $address
   * @param phonenumbertype $phonenumber
   * @param string $title
   * @param date $startdate
   * @param date $enddate
   * @access public
   */
  public function __construct($companyname, $fein, $address, $phonenumber, $title, $startdate, $enddate)
  {
    $this->companyname = $companyname;
    $this->fein = $fein;
    $this->address = $address;
    $this->phonenumber = $phonenumber;
    $this->title = $title;
    $this->startdate = $startdate;
    $this->enddate = $enddate;
  }

}
