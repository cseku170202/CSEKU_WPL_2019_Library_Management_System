<?php

include_once './util/class.util.inc';
include_once './modules/library/dao/class.shelfdao.inc';


/*
	Shelf Business Object 
*/
Class ShelfBAO{

	private $_DB;
	private $_ShelfDAO;


	public function __construct(){

		$this->_ShelfDAO = new ShelfDAO();
	}

	//get all shelfs value
	public function getAllShelves($LibraryId){

		$Result = new Result();	
		$Result = $this->_ShelfDAO->getAllShelves($LibraryId);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in ShelfDAO.getAllShelves()");		

		return $Result;
	}

	
	//create shelf funtion with the shelf object
	public function createShelf($Shelf){

		$Result = new Result();	
		$Result = $this->_ShelfDAO->createShelf($Shelf);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in ShelfDAO.createShelf()");		

		return $Result;

	}


	//search an shelf object
	public function searchShelf($SearchField,$SearchText){


		$Result = new Result();	
		$Result = $this->_ShelfDAO->searchShelf($SearchField,$SearchText);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("No Shelf found!!");		

		return $Result;


	}

	
	//update an shelf object based on its current information
	public function updateShelf($Shelf){

		$Result = new Result();	
		$Result = $this->_ShelfDAO->updateShelf($Shelf);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in ShelfDAO.updateShelf()");		

		return $Result;
	}


	//delete an existing shelf
	public function deleteShelf($Shelf){

		$Result = new Result();	
		$Result = $this->_ShelfDAO->deleteShelf($Shelf);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in ShelfDAO.deleteShelf()");		

		return $Result;

	}
	public function getShelf($Shelf)
	{
		$Result = new Result();	
		$Result = $this->_ShelfDAO->getShelf($Shelf);
			
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in ShelfDAO.getShelf()");		

		return $Result;
	}

	public function getLibraryId($UserId)
	{
		$Result = new Result();	
		$Result = $this->_ShelfDAO->getLibraryId($UserId);
			
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in ShelfDAO.getShelf()");		

		return $Result;
	}

	public function getShelfByLibrary($Shelf)
	{
		$Result = new Result();	
		$Result = $this->_ShelfDAO->getShelfByLibrary($Shelf);
			
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in BooksDAO.getBooks()");		

		return $Result;
	}



}

//echo '<br> log:: exit the class.shelfbao.inc';

?>