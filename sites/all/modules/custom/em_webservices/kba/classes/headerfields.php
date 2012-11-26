<?php

class headerfields
{

  /**
   * 
   * @var headerfieldtype $headerfield
   * @access public
   */
  public $headerfield;

  /**
   * 
   * @var headerfieldvaluetype $headervalue
   * @access public
   */
  public $headervalue;

  /**
   * 
   * @param headerfieldtype $headerfield
   * @param headerfieldvaluetype $headervalue
   * @access public
   */
  public function __construct($headerfield, $headervalue)
  {
    $this->headerfield = $headerfield;
    $this->headervalue = $headervalue;
  }

}
