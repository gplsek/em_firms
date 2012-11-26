<?php

class answertype
{

  /**
   * 
   * @var int $questionid
   * @access public
   */
  public $questionid;

  /**
   * 
   * @var choicestype $choices
   * @access public
   */
  public $choices;

  /**
   * 
   * @param int $questionid
   * @param choicestype $choices
   * @access public
   */
  public function __construct($questionid, $choices)
  {
    $this->questionid = $questionid;
    $this->choices = $choices;
  }

}
