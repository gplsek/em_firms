<?php

class securityquestiontype
{

  /**
   * 
   * @var securityquestioncategorytype $securityquestionquestioncategory
   * @access public
   */
  public $securityquestionquestioncategory;

  /**
   * 
   * @var securityquestionstatementtype $securityquestionquesitonstatement
   * @access public
   */
  public $securityquestionquesitonstatement;

  /**
   * 
   * @var securityquestionanswertype $securityquestionanswer
   * @access public
   */
  public $securityquestionanswer;

  /**
   * 
   * @param securityquestioncategorytype $securityquestionquestioncategory
   * @param securityquestionstatementtype $securityquestionquesitonstatement
   * @param securityquestionanswertype $securityquestionanswer
   * @access public
   */
  public function __construct($securityquestionquestioncategory, $securityquestionquesitonstatement, $securityquestionanswer)
  {
    $this->securityquestionquestioncategory = $securityquestionquestioncategory;
    $this->securityquestionquesitonstatement = $securityquestionquesitonstatement;
    $this->securityquestionanswer = $securityquestionanswer;
  }

}
