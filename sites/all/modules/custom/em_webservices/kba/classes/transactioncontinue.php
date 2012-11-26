<?php

class transactioncontinue
{

  /**
   * 
   * @var continuesettingstype $settings
   * @access public
   */
  public $settings;

  /**
   * 
   * @var answerstype $answers
   * @access public
   */
  public $answers;

  /**
   * 
   * @param continuesettingstype $settings
   * @param answerstype $answers
   * @access public
   */
  public function __construct($settings, $answers)
  {
    $this->settings = $settings;
    $this->answers = $answers;
  }

}
