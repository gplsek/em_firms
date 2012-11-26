<?php

class shippingtype
{

  /**
   * 
   * @var billtotype $billto
   * @access public
   */
  public $billto;

  /**
   * 
   * @var shiptotype $shipto
   * @access public
   */
  public $shipto;

  /**
   * 
   * @var shippingmethod $shippingmethod
   * @access public
   */
  public $shippingmethod;

  /**
   * 
   * @param billtotype $billto
   * @param shiptotype $shipto
   * @param shippingmethod $shippingmethod
   * @access public
   */
  public function __construct($billto, $shipto, $shippingmethod)
  {
    $this->billto = $billto;
    $this->shipto = $shipto;
    $this->shippingmethod = $shippingmethod;
  }

}
