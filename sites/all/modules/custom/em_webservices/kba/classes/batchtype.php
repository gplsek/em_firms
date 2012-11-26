<?php

class batchtype
{

  /**
   * 
   * @var batchidtype $batchid
   * @access public
   */
  public $batchid;

  /**
   * 
   * @param batchidtype $batchid
   * @access public
   */
  public function __construct($batchid)
  {
    $this->batchid = $batchid;
  }

}
