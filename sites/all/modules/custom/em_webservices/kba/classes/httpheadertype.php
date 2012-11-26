<?php

class httpheadertype
{

  /**
   * 
   * @var headertype $header
   * @access public
   */
  public $header;

  /**
   * 
   * @var headerfields $headerfields
   * @access public
   */
  public $headerfields;

  /**
   * 
   * @param headertype $header
   * @param headerfields $headerfields
   * @access public
   */
  public function __construct($header, $headerfields)
  {
    $this->header = $header;
    $this->headerfields = $headerfields;
  }

}
