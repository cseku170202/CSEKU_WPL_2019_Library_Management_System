<?php

include_once './util/class.util.inc';
include_once './modules/library/dao/class.booksdao.inc';
include_once './modules/library/dao/class.browse_librarydao.inc';


/*
	Browse_Library Business Object 
*/
Class Browse_LibraryBAO{


	private $_DB;
	private $_Browse_LibraryDAO;

    /*
	function Browse_LibraryBAO(){

		$this->_Browse_LibraryDAO = new Browse_LibraryDAO();

	}
    */

	public function __construct(){

         $this->_Browse_LibraryDAO = new Browse_LibraryDAO();

	}

	//get all browse_library value
	public function getAllBrowse_Library($LibraryId){

		$Result = new Result();	
		$Result = $this->_Browse_LibraryDAO->getAllBrowse_Library($LibraryId);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in Browse_LibraryDAO.getAllBrowse_Library()");		

		return $Result;
	}

	
	//create browse_library funtion with the browse_library object
	public function addToCart($Browse_Library){

		$Result = new Result();	
		$Result = $this->_Browse_LibraryDAO->addToCart($Browse_Library);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in Browse_LibraryDAO.createBrowse_Library()");		

		return $Result;

	}

	//get all paginated books 
    public function getLimitBooks($page,$limit){
        $Result=$this->_Browse_LibraryDAO->getLimitBooks($page,$limit);

        if(!$Result->getIsSuccess()){
            $Result->setResultObject("Database failure in Browse_LibraryDAO.getLimitBooks($page,$limit)");
        }

        return $Result;
    }

    //get all paginated books 
    public function getLibraryLimitBooks($libraryId,$page,$limit){
        $Result=$this->_Browse_LibraryDAO->getLibraryLimitBooks($libraryId,$page,$limit);

        if(!$Result->getIsSuccess()){
            $Result->setResultObject("Database failure in Browse_LibraryDAO.getLibraryLimitBooks($libraryId,$page,$limit)");
        }

        return $Result;
    }


}

//echo '<br> log:: exit the class.browse_librarybao.inc';

?>