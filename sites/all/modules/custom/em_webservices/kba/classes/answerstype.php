<?php

class answerstype
{

  /**
   * 
   * @var int $questionsetid
   * @access public
   */
  public $questionsetid;

  /**
   * 
   * @var answertype $answer
   * @access public
   */
  public $answer;

  /**
   * 
   * @param int $questionsetid
   * @param answertype $answer
   * @access public
   */
  public function __construct($questionsetid, $answer)
  {
    $this->questionsetid = $questionsetid;
    $this->answer = $answer;
  }

}
