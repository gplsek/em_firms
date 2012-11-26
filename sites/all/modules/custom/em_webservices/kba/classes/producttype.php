<?php

class producttype
{

  /**
   * 
   * @var productcategorytype $productcategory
   * @access public
   */
  public $productcategory;

  /**
   * 
   * @var string $model
   * @access public
   */
  public $model;

  /**
   * 
   * @var string $vendor
   * @access public
   */
  public $vendor;

  /**
   * 
   * @var string $code
   * @access public
   */
  public $code;

  /**
   * 
   * @var string $symbol
   * @access public
   */
  public $symbol;

  /**
   * 
   * @var transactiondirectiontype $transactiondirection
   * @access public
   */
  public $transactiondirection;

  /**
   * 
   * @var int $productquantity
   * @access public
   */
  public $productquantity;

  /**
   * 
   * @var float $peritemamount
   * @access public
   */
  public $peritemamount;

  /**
   * 
   * @var transactiondatetype $transactiondate
   * @access public
   */
  public $transactiondate;

  /**
   * 
   * @var complexdetailtype $data
   * @access public
   */
  public $data;

  /**
   * 
   * @param productcategorytype $productcategory
   * @param string $model
   * @param string $vendor
   * @param string $code
   * @param string $symbol
   * @param transactiondirectiontype $transactiondirection
   * @param int $productquantity
   * @param float $peritemamount
   * @param transactiondatetype $transactiondate
   * @param complexdetailtype $data
   * @access public
   */
  public function __construct($productcategory, $model, $vendor, $code, $symbol, $transactiondirection, $productquantity, $peritemamount, $transactiondate, $data)
  {
    $this->productcategory = $productcategory;
    $this->model = $model;
    $this->vendor = $vendor;
    $this->code = $code;
    $this->symbol = $symbol;
    $this->transactiondirection = $transactiondirection;
    $this->productquantity = $productquantity;
    $this->peritemamount = $peritemamount;
    $this->transactiondate = $transactiondate;
    $this->data = $data;
  }

}
