<?php

include_once './util/class.util.inc';
include_once './modules/library/dao/class.issuancedao.inc';


/*
	Issuance Business Object 
*/
Class IssuanceBAO{


	private $_DB;
	private $_IssuanceDAO;
	
    /*
	function IssuanceBAO(){

		$this->_IssuanceDAO = new IssuanceDAO();

	}
    */

	public function __construct(){

		$this->_IssuanceDAO = new IssuanceDAO();
	}

	//get all issuance value
	public function getAllIssuance($LibraryId){

		$Result = new Result();	
		$Result = $this->_IssuanceDAO->getAllIssuance($LibraryId);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in IssuanceDAO.getAllIssuance()");		

		return $Result;
	}


		//get all issuance value
	public function getAllApprovedIssuance($LibraryId){

		$Result = new Result();	
		$Result = $this->_IssuanceDAO->getAllApprovedIssuance($LibraryId);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in IssuanceDAO.getAllIssuance()");		

		return $Result;
	}

	//get  issuance by userID
	public function getIssuanceByUserId($UserId){

		$Result = new Result();	
		$Result = $this->_IssuanceDAO->getIssuanceByUserId($UserId);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in IssuanceDAO.getIssuanceByUserId()");		

		return $Result;
	}

	
	//create issuance funtion with the issuance object
	public function createIssuance($Issuance){

		$Result = new Result();	
		$Result = $this->_IssuanceDAO->createIssuance($Issuance);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in IssuanceDAO.createIssuance()");		

		return $Result;

	}


	//sort issuance objects
	public  function sortIssuanceByStatus($LibraryId,$SearchField,$SearchText){


		$Result = new Result();	
		$Result = $this->_IssuanceDAO->sortIssuanceByStatus($LibraryId,$SearchField,$SearchText);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("No Issuance found!!");		

		return $Result;


	}
	//search an issuance object
	public function searchIssuance($LibraryId,$SearchText){


		$Result = new Result();	
		$Result = $this->_IssuanceDAO->searchIssuance($LibraryId,$SearchText);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("No Issuance found!!");		

		return $Result;


	}
	//approveIssuance an issuance
	public function approveIssuance($Issuance){

		$Result = new Result();	
		$Result = $this->_IssuanceDAO->approveIssuance($Issuance);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in IssuanceDAO.approveIssuance()");		

		return $Result;

	}
	public function setNotification($Notify){

		$Result = new Result();	
		$Result = $this->_IssuanceDAO->setNotification($Notify);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in IssuanceDAO.setNotification()");		

		return $Result;

	}

	//completeIssuance an issuance
	//public function completeIssuance($Issuance){
	public function receiveIssuance($Issuance){

		$Result = new Result();	
		//$Result = $this->_IssuanceDAO->completeIssuance($Issuance);
		$Result = $this->_IssuanceDAO->receiveIssuance($Issuance);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in IssuanceDAO.completeIssuance()");		

		return $Result;

	}

	//delete an existing issuance
	public function deleteIssuance($Issuance){

		$Result = new Result();	
		$Result = $this->_IssuanceDAO->deleteIssuance($Issuance);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in IssuanceDAO.deleteIssuance()");		

		return $Result;

	}
	public function getIssuance($Issuance)
	{
		$Result = new Result();	
		$Result = $this->_IssuanceDAO->getIssuance($Issuance);
			
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in IssuanceDAO.getIssuance()");		

		return $Result;
	}


	public function payReceived($Issuance)
	{
		$Result = new Result();	
		$Result = $this->_IssuanceDAO->payReceived($Issuance);
			
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in IssuanceDAO.payReceived()");		

		return $Result;
	}

}

//echo '<br> log:: exit the class.issuancebao.inc';

?>