<?php

class riskassessmenttype
{

  /**
   * 
   * @var riskscore $riskscore
   * @access public
   */
  public $riskscore;

  /**
   * 
   * @var threatassessment $threatassessment
   * @access public
   */
  public $threatassessment;

  /**
   * 
   * @var riskcomponenttype $riskcomponent
   * @access public
   */
  public $riskcomponent;

  /**
   * 
   * @param riskscore $riskscore
   * @param threatassessment $threatassessment
   * @param riskcomponenttype $riskcomponent
   * @access public
   */
  public function __construct($riskscore, $threatassessment, $riskcomponent)
  {
    $this->riskscore = $riskscore;
    $this->threatassessment = $threatassessment;
    $this->riskcomponent = $riskcomponent;
  }

}
