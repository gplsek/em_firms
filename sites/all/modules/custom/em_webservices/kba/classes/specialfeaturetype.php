<?php

class specialfeaturetype
{

  /**
   * 
   * @var specialfeaturecodetype $specialfeaturecode
   * @access public
   */
  public $specialfeaturecode;

  /**
   * 
   * @var specialfeaturevaluetype $specialfeaturevalue
   * @access public
   */
  public $specialfeaturevalue;

  /**
   * 
   * @param specialfeaturecodetype $specialfeaturecode
   * @param specialfeaturevaluetype $specialfeaturevalue
   * @access public
   */
  public function __construct($specialfeaturecode, $specialfeaturevalue)
  {
    $this->specialfeaturecode = $specialfeaturecode;
    $this->specialfeaturevalue = $specialfeaturevalue;
  }

}
