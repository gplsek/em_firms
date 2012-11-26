<?php

class phonenumbertype
{

  /**
   * 
   * @var string $phonenumber
   * @access public
   */
  public $phonenumber;

  /**
   * 
   * @var phonenumbercontexttype $phonenumbercontext
   * @access public
   */
  public $phonenumbercontext;

  /**
   * 
   * @param string $phonenumber
   * @param phonenumbercontexttype $phonenumbercontext
   * @access public
   */
  public function __construct($phonenumber, $phonenumbercontext)
  {
    $this->phonenumber = $phonenumber;
    $this->phonenumbercontext = $phonenumbercontext;
  }

}
