<?php

class orderedbytype
{

  /**
   * 
   * @var sameastype $sameas
   * @access public
   */
  public $sameas;

  /**
   * 
   * @var persontype $person
   * @access public
   */
  public $person;

  /**
   * 
   * @param sameastype $sameas
   * @param persontype $person
   * @access public
   */
  public function __construct($sameas, $person)
  {
    $this->sameas = $sameas;
    $this->person = $person;
  }

}
