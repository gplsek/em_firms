<?php

class shiptotype
{

  /**
   * 
   * @var sameastype $sameas
   * @access public
   */
  public $sameas;

  /**
   * 
   * @var persontype $persontype
   * @access public
   */
  public $persontype;

  /**
   * 
   * @param sameastype $sameas
   * @param persontype $persontype
   * @access public
   */
  public function __construct($sameas, $persontype)
  {
    $this->sameas = $sameas;
    $this->persontype = $persontype;
  }

}
