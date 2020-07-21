<?php

include_once './util/class.util.inc';
include_once './modules/library/dao/class.librarydao.inc';

/*
	Library Business Object 
*/
Class LibraryBAO{

	private $_DB;
	private $_LibraryDAO;


	public function __construct(){

		$this->_LibraryDAO = new LibraryDAO();
	}

	//get all librarys value
	public function getAllLibraries(){

		$Result = new Result();	
		$Result = $this->_LibraryDAO->getAllLibraries();
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in LibraryDAO.getAllLibraries()");		

		return $Result;
	}

	
	//create library funtion with the library object
	public function createLibrary($Library){

		$Result = new Result();	
		$Result = $this->_LibraryDAO->createLibrary($Library);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in LibraryDAO.createLibrary()");		

		return $Result;

	}


	//search an library object
	public function searchLibrary($SearchField,$SearchText){


		$Result = new Result();	
		$Result = $this->_LibraryDAO->searchLibrary($SearchField,$SearchText);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("No Library found!!");		

		return $Result;


	}

	
	//update an library object based on its current information
	public function updateLibrary($Library){

		$Result = new Result();	
		$Result = $this->_LibraryDAO->updateLibrary($Library);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in LibraryDAO.updateLibrary()");		

		return $Result;
	}


	//delete an existing library
	public function deleteLibrary($Library){

		$Result = new Result();	
		$Result = $this->_LibraryDAO->deleteLibrary($Library);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in LibraryDAO.deleteLibrary()");		

		return $Result;

	}
	public function getLibrary($Library)
	{
		$Result = new Result();	
		$Result = $this->_LibraryDAO->getLibrary($Library);
			
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in LibraryDAO.getLibrary()");		

		return $Result;
	}

}

//echo '<br> log:: exit the class.librarybao.inc';

?>