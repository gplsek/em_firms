<?php

class credentialtype
{

  /**
   * 
   * @var credentialmethodtype $credentialmethod
   * @access public
   */
  public $credentialmethod;

  /**
   * 
   * @var usernametype $username
   * @access public
   */
  public $username;

  /**
   * 
   * @var domaintype $domain
   * @access public
   */
  public $domain;

  /**
   * 
   * @var organizationalunittype $organizationalunit
   * @access public
   */
  public $organizationalunit;

  /**
   * 
   * @var httpheadertype $httpheader
   * @access public
   */
  public $httpheader;

  /**
   * 
   * @var ipaddresstype $ipaddress
   * @access public
   */
  public $ipaddress;

  /**
   * 
   * @var machineidtype $machineid
   * @access public
   */
  public $machineid;

  /**
   * 
   * @param credentialmethodtype $credentialmethod
   * @param usernametype $username
   * @param domaintype $domain
   * @param organizationalunittype $organizationalunit
   * @param httpheadertype $httpheader
   * @param ipaddresstype $ipaddress
   * @param machineidtype $machineid
   * @access public
   */
  public function __construct($credentialmethod, $username, $domain, $organizationalunit, $httpheader, $ipaddress, $machineid)
  {
    $this->credentialmethod = $credentialmethod;
    $this->username = $username;
    $this->domain = $domain;
    $this->organizationalunit = $organizationalunit;
    $this->httpheader = $httpheader;
    $this->ipaddress = $ipaddress;
    $this->machineid = $machineid;
  }

}
