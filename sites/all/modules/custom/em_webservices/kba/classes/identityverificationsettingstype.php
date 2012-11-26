<?php

class identityverificationsettingstype
{

  /**
   * 
   * @var tasktype $task
   * @access public
   */
  public $task;

  /**
   * 
   * @var int $sequenceid
   * @access public
   */
  public $sequenceid;

  /**
   * 
   * @var string $agent
   * @access public
   */
  public $agent;

  /**
   * 
   * @var boolean $patriotactcompliance
   * @access public
   */
  public $patriotactcompliance;

  /**
   * 
   * @var transactionidtype $parenttransactionid
   * @access public
   */
  public $parenttransactionid;

  /**
   * 
   * @param tasktype $task
   * @param int $sequenceid
   * @param string $agent
   * @param boolean $patriotactcompliance
   * @param transactionidtype $parenttransactionid
   * @access public
   */
  public function __construct($task, $sequenceid, $agent, $patriotactcompliance, $parenttransactionid)
  {
    $this->task = $task;
    $this->sequenceid = $sequenceid;
    $this->agent = $agent;
    $this->patriotactcompliance = $patriotactcompliance;
    $this->parenttransactionid = $parenttransactionid;
  }

}
