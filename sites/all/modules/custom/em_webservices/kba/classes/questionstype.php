<?php

class questionstype
{

  /**
   * 
   * @var int $questionsetid
   * @access public
   */
  public $questionsetid;

  /**
   * 
   * @var questiontype $question
   * @access public
   */
  public $question;

  /**
   * 
   * @param int $questionsetid
   * @param questiontype $question
   * @access public
   */
  public function __construct($questionsetid, $question)
  {
    $this->questionsetid = $questionsetid;
    $this->question = $question;
  }

}
