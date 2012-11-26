<?php

class order
{

  /**
   * 
   * @var producttype $item
   * @access public
   */
  public $item;

  /**
   * 
   * @var float $totalamount
   * @access public
   */
  public $totalamount;

  /**
   * 
   * @var float $totaltax
   * @access public
   */
  public $totaltax;

  /**
   * 
   * @var float $totalshipping
   * @access public
   */
  public $totalshipping;

  /**
   * 
   * @var string $merchant
   * @access public
   */
  public $merchant;

  /**
   * 
   * @param producttype $item
   * @param float $totalamount
   * @param float $totaltax
   * @param float $totalshipping
   * @param string $merchant
   * @access public
   */
  public function __construct($item, $totalamount, $totaltax, $totalshipping, $merchant)
  {
    $this->item = $item;
    $this->totalamount = $totalamount;
    $this->totaltax = $totaltax;
    $this->totalshipping = $totalshipping;
    $this->merchant = $merchant;
  }

}
