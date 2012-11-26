<?php

class complexdetailtype
{

  /**
   * 
   * @var string $heading
   * @access public
   */
  public $heading;

  /**
   * 
   * @var simpledetailtype $simpledetail
   * @access public
   */
  public $simpledetail;

  /**
   * 
   * @var complexdetailtype $complexdetail
   * @access public
   */
  public $complexdetail;

  /**
   * 
   * @param string $heading
   * @param simpledetailtype $simpledetail
   * @param complexdetailtype $complexdetail
   * @access public
   */
  public function __construct($heading, $simpledetail, $complexdetail)
  {
    $this->heading = $heading;
    $this->simpledetail = $simpledetail;
    $this->complexdetail = $complexdetail;
  }

}
