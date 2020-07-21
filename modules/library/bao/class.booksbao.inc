<?php

include_once './util/class.util.inc';
include_once './modules/library/dao/class.booksdao.inc';


/*
	Books Business Object 
*/
Class BooksBAO{

	private $_DB;
	private $_BooksDAO;

    /*
	function BooksBAO(){

		$this->_BooksDAO = new BooksDAO();

	}
	*/

    public function __construct(){

    	$this->_BooksDAO = new BooksDAO();
    }

	//get all books value
	public function getAllBooks($libraryId){

		$Result = new Result();	
		$Result = $this->_BooksDAO->getAllBooks($libraryId);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in BooksDAO.getAllBooks()");		

		return $Result;
	}
	//get getAllLibraryBooks
	public function getAllLibraryBooks(){

		$Result = new Result();	
		$Result = $this->_BooksDAO->getAllLibraryBooks();
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in BooksDAO.getAllLibraryBooks()");		

		return $Result;
	}


	
	//create books funtion with the books object
	public function createBooks($Books){

		$Result = new Result();	
		$Result = $this->_BooksDAO->createBooks($Books);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in BooksDAO.createBooks()");		

		return $Result;

	}


	//search an books object
	public function searchBooks($SearchText,$LibraryId){


		$Result = new Result();	
		$Result = $this->_BooksDAO->searchBooks($SearchText,$LibraryId);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("No Books found!!");		

		return $Result;


	}

	
	//update an books object based on its current information
	public function updateBooks($Books){

		$Result = new Result();	
		$Result = $this->_BooksDAO->updateBooks($Books);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in BooksDAO.updateBooks()");		

		return $Result;
	}


	//delete an existing books
	public function deleteBooks($Books){

		$Result = new Result();	
		$Result = $this->_BooksDAO->deleteBooks($Books);
		
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in BooksDAO.deleteBooks()");		

		return $Result;

	}
	public function getBooks($Books)
	{
		$Result = new Result();	
		$Result = $this->_BooksDAO->getBooks($Books);
			
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in BooksDAO.getBooks()");		

		return $Result;
	}
	public function getBooksByShelf($Books)
	{
		$Result = new Result();	
		$Result = $this->_BooksDAO->getBooksByShelf($Books);
			
		if(!$Result->getIsSuccess())
			$Result->setResultObject("Database failure in BooksDAO.getBooks()");		

		return $Result;
	}

	
    //upload thesis thumbnails
    public function uploadThumbnail($Books){
        $Upload=$this->_BooksDAO->uploadThumbnail($Books);

        return $Upload;
    }

    //delete thesis thumbnail
    public function deleteThumbnail($Books){
        $Delete=$this->_BooksDAO->deleteThumbnail($Books);

        return $Delete;
    }

}

//echo '<br> log:: exit the class.booksbao.inc';

?>