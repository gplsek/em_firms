<?php

class birthdatetype
{

  /**
   * 
   * @var yeartype $year
   * @access public
   */
  public $year;

  /**
   * 
   * @var monthtype $month
   * @access public
   */
  public $month;

  /**
   * 
   * @var daytype $day
   * @access public
   */
  public $day;

  /**
   * 
   * @param yeartype $year
   * @param monthtype $month
   * @param daytype $day
   * @access public
   */
  public function __construct($year, $month, $day)
  {
    $this->year = $year;
    $this->month = $month;
    $this->day = $day;
  }

}
