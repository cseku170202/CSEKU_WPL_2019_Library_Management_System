<?php

include_once './util/class.util.inc';
include_once './modules/library/dao/class.checkoutdao.inc';


/*
	Checkout Business Object 
*/
Class CheckoutBAO{


	private $_DB;
	private $_CheckoutDAO;

    /*
	function CheckoutBAO(){

		$this->_CheckoutDAO = new CheckoutDAO();

	}
	*/

	public function __construct(){

		$this->_CheckoutDAO = new CheckoutDAO();
	}

	//get all checkout value
	public function getCart($UserId){

		$Result = new Result();	
		$Result = $this->_CheckoutDAO->getCart($UserId);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in CheckoutDAO.getCart()");		

		return $Result;
	}

	
	//delete an existing checkout
	public function removeFromCart($Checkout){

		$Result = new Result();	
		$Result = $this->_CheckoutDAO->removeFromCart($Checkout);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in CheckoutDAO.removeFromCart()");		

		return $Result;

	}

	//checkout 
	public function completeCheckout($UserId){

		$Result = new Result();	
		$Result = $this->_CheckoutDAO->completeCheckout($UserId);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in CheckoutDAO.completeCheckout()");		

		return $Result;

	}


}

//echo '<br> log:: exit the class.checkoutbao.inc';

?>