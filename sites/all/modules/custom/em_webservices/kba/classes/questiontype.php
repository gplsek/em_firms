<?php

class questiontype
{

  /**
   * 
   * @var int $questionid
   * @access public
   */
  public $questionid;

  /**
   * 
   * @var answerselectiontype $answertype
   * @access public
   */
  public $answertype;

  /**
   * 
   * @var texttype $text
   * @access public
   */
  public $text;

  /**
   * 
   * @var choicetype $choice
   * @access public
   */
  public $choice;

  /**
   * 
   * @var texttype $helptext
   * @access public
   */
  public $helptext;

  /**
   * 
   * @param int $questionid
   * @param answerselectiontype $answertype
   * @param texttype $text
   * @param choicetype $choice
   * @param texttype $helptext
   * @access public
   */
  public function __construct($questionid, $answertype, $text, $choice, $helptext)
  {
    $this->questionid = $questionid;
    $this->answertype = $answertype;
    $this->text = $text;
    $this->choice = $choice;
    $this->helptext = $helptext;
  }

}
