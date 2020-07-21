<?php

include_once './util/class.util.inc';
include_once './modules/library/dao/class.testdao.inc';


/*
	Shelf Business Object 
*/
Class FineBAO{

	private $_DB;
	private $_FineDAO;


	public function __construct(){

		$this->_FineDAO = new FineDAO();
	}


	public function getLibraryFine(){

		$Result = new Result();	
		$Result = $this->_FineDAO->getLibraryFine();
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in LibraryDAO.getAllLibraries()");		

		return $Result;
	}

	
	//create shelf funtion with the shelf object
	public function createUserFine($Fine){

		$Result = new Result();	
		$Result = $this->_FineDAO->createUserFine($Fine);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in FineDAO.createUserFine()");		

		return $Result;

	}


	//update an shelf object based on its current information
	public function updateUserFine($Fine){

		$Result = new Result();	
		$Result = $this->_FineDAO->updateUserFine($Fine);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in FineDAO.updateUserFine()");		

		return $Result;
	}


	//delete an existing shelf
	public function deleteUserFine($Fine){

		$Result = new Result();	
		$Result = $this->_FineDAO->deleteUserFine($Fine);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in FineDAO.deleteUserFine()");		

		return $Result;

	}
	public function getUserFine($Fine)
	{
		$Result = new Result();	
		$Result = $this->_FineDAO->getUserFine($Fine);
			
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in FineDAO.getUserFine()");		

		return $Result;
	}



	public function getLibraryId($UserId)
	{
		$Result = new Result();	
		$Result = $this->_FineDAO->getLibraryId($UserId);
			
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in ShelfDAO.getShelf()");		

		return $Result;
	}


	
}

//echo '<br> log:: exit the class.testbao.inc';

?>