<?php

class riskcomponenttype
{

  /**
   * 
   * @var riskcategory $riskcategory
   * @access public
   */
  public $riskcategory;

  /**
   * 
   * @var riskscore $riskscore
   * @access public
   */
  public $riskscore;

  /**
   * 
   * @param riskcategory $riskcategory
   * @param riskscore $riskscore
   * @access public
   */
  public function __construct($riskcategory, $riskscore)
  {
    $this->riskcategory = $riskcategory;
    $this->riskscore = $riskscore;
  }

}
