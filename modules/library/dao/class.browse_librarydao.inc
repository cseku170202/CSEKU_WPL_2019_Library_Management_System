<?php
// write dao object for each class
include_once './common/class.common.inc';
include_once './util/class.util.inc';
include_once './common/class.common.library.inc';

Class Browse_LibraryDao{

	private $_DB;
	private $_Browse_Library;
	private $_Books;


	function Browse_LibraryDao(){

		$this->_DB = DBUtil::getInstance();
		//$this->$_Books=new Books();

	}

	// get all the browse_library from the database using the database query
	public function getAllBrowse_Library($LibraryId){

		$Browse_LibraryList = array();

		$this->_DB->doQuery("SELECT lms_books.serialNo,lms_books.title,lms_books.author,browse_library.id as Browse_LibraryID,browse_library.* FROM browse_library,lms_books,shelf WHERE browse_library.bookId = lms_books.id && lms_books.shelfId = shelf.id && shelf.libraryId = '".$LibraryId."'");

		$rows = $this->_DB->getAllRows();

		for($i = 0; $i < sizeof($rows); $i++) {
			$row = $rows[$i];
			$this->_Browse_Library = new Browse_Library();

		    $this->_Browse_Library->setID ( $row['Browse_LibraryID']);
		    $this->_Browse_Library->setBookId ( $row['bookId'] );   
		    $this->_Browse_Library->setIssuedTo( $row['issuedTo'] );
		    $this->_Browse_Library->setIssueDate( $row['issueDate'] );
		    $this->_Browse_Library->setReturnDate( $row['returnDate'] );
		    $this->_Browse_Library->setStatus( $row['status'] );
		

		    $Browse_LibraryList[]=$this->_Browse_Library;
   
		}

		//todo: LOG util with level of log
		//echo '<br> log::complete getAllLibraries::'.print_r($Browse_LibraryList);

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($Browse_LibraryList);

		return $Result;
	}


	//create browse_library funtion with the browse_library object
	public function addToCart($Browse_Library){

		$ID=$Browse_Library->getID();
		$bookId=$Browse_Library->getBookId();
		$userId=$Browse_Library->getUserId();


		$SQL = "INSERT INTO lms_cart VALUES('$ID','$bookId','$userId')";


		//creating the browse_library
		$SQL = $this->_DB->doQuery($SQL);


	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);

		return $Result;
	}


	 //get paginated thesis
    public function getLimitBooks($page,$limit){
        $BooksList=array();
        $SQL="SELECT * FROM lms_books LIMIT $page,$limit";
        $this->_DB->doQuery($SQL);

        $rows=$this->_DB->getAllRows();
        foreach ($rows as $row){
            $this->_Books=new Books();
            $this->_Books->setID($row['id']);
            $this->_Books->setSerialNo($row['serialNo']);
            $this->_Books->setTitle($row['title']);
            $this->_Books->setAuthor($row['author']);
            $this->_Books->setShelfId($row['shelfId']);
            $this->_Books->setAvailableCopies($row['availableCopies']);
            $this->_Books->setCover($row['cover']);


            $BooksList[]=$this->_Books;
        }

        
        $Result=new Result();
        $Result->setIsSuccess(1);
        $Result->setResultObject($BooksList);
        
        return $Result;
    }




    	// get all the books from the database using the database query
	public function getLibraryLimitBooks($libraryId,$page,$limit)
	{

		$BooksList = array();

		$SQL="SELECT lms_books.*,lms_shelf.id as shelfId FROM lms_books,lms_shelf WHERE lms_books.shelfId = lms_shelf.id && lms_shelf.libraryId = '.$libraryId.' LIMIT $page,$limit";
		$this->_DB->doQuery($SQL);

		$rows = $this->_DB->getAllRows();

		  foreach ($rows as $row){
            $this->_Books=new Books();
            $this->_Books->setID($row['id']);
            $this->_Books->setSerialNo($row['serialNo']);
            $this->_Books->setTitle($row['title']);
            $this->_Books->setAuthor($row['author']);
            $this->_Books->setShelfId($row['shelfId']);
            $this->_Books->setAvailableCopies($row['availableCopies']);
            $this->_Books->setCover($row['cover']);


            $BooksList[]=$this->_Books;
        }

		//todo: LOG util with level of log
		//echo '<br> log::complete getAllLibraries::'.print_r($BooksList);

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($BooksList);

		return $Result;
	}

}

//echo '<br> log:: exit the class.browse_librarydao.inc';

?>