<?php

class transactionresponse
{

  /**
   * 
   * @var transactionstatustype $transactionstatus
   * @access public
   */
  public $transactionstatus;

  /**
   * 
   * @var questionstype $questions
   * @access public
   */
  public $questions;

  /**
   * 
   * @var informationtype $information
   * @access public
   */
  public $information;

  /**
   * 
   * @param transactionstatustype $transactionstatus
   * @param questionstype $questions
   * @param informationtype $information
   * @access public
   */
  public function __construct($transactionstatus, $questions, $information)
  {
    $this->transactionstatus = $transactionstatus;
    $this->questions = $questions;
    $this->information = $information;
  }

}
