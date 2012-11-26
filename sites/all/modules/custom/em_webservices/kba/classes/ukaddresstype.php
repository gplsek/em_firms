<?php

class ukaddresstype
{

  /**
   * 
   * @var string $housename
   * @access public
   */
  public $housename;

  /**
   * 
   * @var string $housenumber
   * @access public
   */
  public $housenumber;

  /**
   * 
   * @var string $street1
   * @access public
   */
  public $street1;

  /**
   * 
   * @var string $street2
   * @access public
   */
  public $street2;

  /**
   * 
   * @var string $district
   * @access public
   */
  public $district;

  /**
   * 
   * @var string $town
   * @access public
   */
  public $town;

  /**
   * 
   * @var string $county
   * @access public
   */
  public $county;

  /**
   * 
   * @var string $postcode
   * @access public
   */
  public $postcode;

  /**
   * 
   * @var addresscontexttype $context
   * @access public
   */
  public $context;

  /**
   * 
   * @var float $yearsat
   * @access public
   */
  public $yearsat;

  /**
   * 
   * @param string $housename
   * @param string $housenumber
   * @param string $street1
   * @param string $street2
   * @param string $district
   * @param string $town
   * @param string $county
   * @param string $postcode
   * @param addresscontexttype $context
   * @param float $yearsat
   * @access public
   */
  public function __construct($housename, $housenumber, $street1, $street2, $district, $town, $county, $postcode, $context, $yearsat)
  {
    $this->housename = $housename;
    $this->housenumber = $housenumber;
    $this->street1 = $street1;
    $this->street2 = $street2;
    $this->district = $district;
    $this->town = $town;
    $this->county = $county;
    $this->postcode = $postcode;
    $this->context = $context;
    $this->yearsat = $yearsat;
  }

}
