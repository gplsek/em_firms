<?php

class informationtype
{

  /**
   * 
   * @var informationcodetype $informationcode
   * @access public
   */
  public $informationcode;

  /**
   * 
   * @var string $detailcode
   * @access public
   */
  public $detailcode;

  /**
   * 
   * @var string $detaildescription
   * @access public
   */
  public $detaildescription;

  /**
   * 
   * @var complexdetailtype $complexdetail
   * @access public
   */
  public $complexdetail;

  /**
   * 
   * @var simpledetailtype $simpledetail
   * @access public
   */
  public $simpledetail;

  /**
   * 
   * @param informationcodetype $informationcode
   * @param string $detailcode
   * @param string $detaildescription
   * @param complexdetailtype $complexdetail
   * @param simpledetailtype $simpledetail
   * @access public
   */
  public function __construct($informationcode, $detailcode, $detaildescription, $complexdetail, $simpledetail)
  {
    $this->informationcode = $informationcode;
    $this->detailcode = $detailcode;
    $this->detaildescription = $detaildescription;
    $this->complexdetail = $complexdetail;
    $this->simpledetail = $simpledetail;
  }

}
