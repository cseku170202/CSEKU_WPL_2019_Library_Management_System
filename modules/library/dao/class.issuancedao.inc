<?php
// write dao object for each class
include_once './common/class.common.inc';
include_once './util/class.util.inc';

Class IssuanceDao{

	private $_DB;
	private $_Issuance;


	function IssuanceDao(){

		$this->_DB = DBUtil::getInstance();

	}

	// get all the issuance from the database using the database query
	public function getAllIssuance($LibraryId){

		$IssuanceList = array();

		$this->_DB->doQuery("SELECT lms_books.serialNo,lms_books.title,lms_books.author,lms_issuance.id as IssuanceID,lms_issuance.* FROM lms_issuance,lms_books,lms_shelf WHERE lms_issuance.bookId = lms_books.id && lms_books.shelfId = lms_shelf.id && lms_shelf.libraryId = '".$LibraryId."' ORDER BY lms_issuance.issueDate DESC");

		$rows = $this->_DB->getAllRows();

		for($i = 0; $i < sizeof($rows); $i++) {
			$row = $rows[$i];
			$this->_Issuance = new Issuance();

		    $this->_Issuance->setID ( $row['IssuanceID']);
		    $this->_Issuance->setBookId ( $row['bookId'] );   
		    $this->_Issuance->setIssuedTo( $row['issuedTo'] );
		    $this->_Issuance->setIssueDate( $row['issueDate'] );
		    $this->_Issuance->setIssuedDate( $row['issuedDate'] );
		    $this->_Issuance->setReturnDate( $row['returnDate'] );
		    $this->_Issuance->setStatus( $row['status'] );
		

		    $IssuanceList[]=$this->_Issuance;
   
		}

		//todo: LOG util with level of log
		//echo '<br> log::complete getAllLibraries::'.print_r($IssuanceList);

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($IssuanceList);

		return $Result;
	}

	// get all the issuance from the database using the database query
	public function getIssuanceByUserId($UserId){

		$IssuanceList = array();

		$this->_DB->doQuery("SELECT lms_books.serialNo,lms_books.title,lms_books.author,lms_issuance.id as IssuanceID,lms_issuance.* FROM lms_issuance,lms_books,lms_shelf,lms_library WHERE lms_issuance.bookId = lms_books.id && lms_books.shelfId = lms_shelf.id && lms_shelf.libraryId = lms_library.id && lms_issuance.issuedTo ='".$UserId."' ORDER BY lms_issuance.issueDate DESC");

		$rows = $this->_DB->getAllRows();

		for($i = 0; $i < sizeof($rows); $i++) {
			$row = $rows[$i];
			$this->_Issuance = new Issuance();

		    $this->_Issuance->setID ( $row['IssuanceID']);
		    $this->_Issuance->setBookId ( $row['bookId'] );   
		    $this->_Issuance->setIssuedTo( $row['issuedTo'] );
		    $this->_Issuance->setIssueDate( $row['issueDate'] );
		    //$this->_Issuance->setIssuedDate( $row['issuedDate'] );
		    $this->_Issuance->setReturnDate( $row['returnDate'] );
		    $this->_Issuance->setStatus( $row['status'] );
		    $this->_Issuance->setIssuedDate( $row['issuedDate'] );
		

		    $IssuanceList[]=$this->_Issuance;
   
		}

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($IssuanceList);

		return $Result;
	}


	//create issuance funtion with the issuance object
	public function createIssuance($Issuance){

		$ID=$Issuance->getID();
		$bookId=$Issuance->getBookId();
		$issuedTo=$Issuance->getIssuedTo();
		$issueDate=$Issuance->getIssueDate();
		//$returnDate=$Issuance->getReturnDate();
		$status=$Issuance->getStatus();
		//$issuedDate=$Issuance->getIssuedD();

	

		//$SQL = "INSERT INTO lms_issuance VALUES('$ID','$bookId','$issuedTo','$issueDate','$returnDate','$status')";


		//$SQL = "INSERT INTO lms_issuance(id,bookId,issuedTo,issueDate,returnDate,status) VALUES('$ID','$bookId','$issuedTo','$issueDate','$returnDate','$status')";

        $SQL = "INSERT INTO lms_issuance(id,bookId,issuedTo,issueDate,status) VALUES('$ID','$bookId','$issuedTo','$issueDate','$status')";



		//creating the issuance
		$SQL = $this->_DB->doQuery($SQL);


	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);

		return $Result;
	}


	//search a issuance object based on some criteria
	public function sortIssuanceByStatus($LibraryId,$SearchField,$SearchText){
		

		$SQL = "SELECT lms_books.serialNo,lms_books.title,lms_books.author,lms_issuance.id as IssuanceID,lms_issuance.* FROM lms_issuance,lms_books,lms_shelf WHERE lms_issuance.bookId = lms_books.id && lms_books.shelfId = lms_shelf.id && lms_shelf.libraryId = '$LibraryId' && $SearchField like '$SearchText'";


		$this->_DB->doQuery($SQL);
		
		$rows = $this->_DB->getAllRows();

		$IssuanceList = array();
		for($i = 0; $i < sizeof($rows); $i++) {
			$row = $rows[$i];
			$this->_Issuance = new Issuance();

		    $this->_Issuance->setID ( $row['IssuanceID']);
		    $this->_Issuance->setBookId ( $row['bookId'] );   
		    $this->_Issuance->setIssuedTo( $row['issuedTo'] );
		    $this->_Issuance->setIssueDate( $row['issueDate'] );
		    $this->_Issuance->setIssuedDate( $row['issuedDate'] );

		    $this->_Issuance->setReturnDate( $row['returnDate'] );
		    $this->_Issuance->setStatus( $row['status'] );

		    $IssuanceList[]=$this->_Issuance;
   
		}

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($IssuanceList);

		return $Result;
	}

	//search a issuance object based on some criteria
	public function searchIssuance($LibraryId,$SearchText){
		

		$SQL = "SELECT lms_books.serialNo,lms_books.title,lms_books.author,lms_issuance.id as IssuanceID,lms_issuance.* FROM lms_issuance,lms_books,lms_shelf,tbl_user WHERE lms_issuance.issuedTo = tbl_user.ID && lms_issuance.bookId = lms_books.id && lms_books.shelfId = lms_shelf.id && lms_shelf.libraryId = '$LibraryId' && (lms_books.serialNo LIKE '$SearchText' || lms_books.title LIKE '$SearchText' || lms_books.author LIKE '$SearchText' || tbl_user.FirstName LIKE '$SearchText' || tbl_user.LastName LIKE '$SearchText' ||  lms_issuance.issueDate LIKE '$SearchText' || lms_issuance.status LIKE '$SearchText' )";


		$this->_DB->doQuery($SQL);
		
		$rows = $this->_DB->getAllRows();
		
		$IssuanceList = array();
		for($i = 0; $i < sizeof($rows); $i++) {
			$row = $rows[$i];
			$this->_Issuance = new Issuance();

		    $this->_Issuance->setID ( $row['IssuanceID']);
		    $this->_Issuance->setBookId ( $row['bookId'] );   
		    $this->_Issuance->setIssuedTo( $row['issuedTo'] );
		    $this->_Issuance->setIssueDate( $row['issueDate'] );
		    $this->_Issuance->setReturnDate( $row['returnDate'] );
		    $this->_Issuance->setStatus( $row['status'] );

		    $IssuanceList[]=$this->_Issuance;
   
		}

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($IssuanceList);

		return $Result;
	}

	//approve an issuance based on its id of the database
	public function approveIssuance($Issuance){


		$SQL = "UPDATE lms_issuance SET status = 'Approved' WHERE id ='".$Issuance->getID()."'";
		$SQL = $this->_DB->doQuery($SQL);

        //Issued date
		$issuedDate = date("Y-m-d");
		$SQL_IssuedDate = "UPDATE lms_issuance SET issuedDate = '$issuedDate' WHERE id ='".$Issuance->getID()."'";
		$SQL = $this->_DB->doQuery($SQL_IssuedDate);

        $Id = $Issuance->getID();
        //return date
		$this->_DB->doQuery("SELECT lms_library.returnPolicy FROM lms_issuance,lms_books,lms_shelf,lms_library WHERE lms_issuance.id='$Id' AND lms_issuance.bookId=lms_books.id AND lms_books.shelfId=lms_shelf.id AND lms_shelf.libraryId=lms_library.id");

		$row=$this->_DB->getTopRow();
        $this->_Issuance = new Issuance();
        $this->_Issuance->setLibraryReturnPolicy( $row['returnPolicy'] );
        $returnDate =  date('Y-m-d', strtotime($issuedDate.'+'.$row['returnPolicy'].'days'));

        $SQL_ReturnDate = "UPDATE lms_issuance SET returnDate = '$returnDate' WHERE id ='".$Issuance->getID()."'";
		$SQL = $this->_DB->doQuery($SQL_ReturnDate);



	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);

		return $Result;

	}
	public function setNotification($Notify)
	{
		$SQL = "INSERT INTO `notify`(`id`, `message`, `toUser`, `fromModule`, `isSeen`, `isSent`) VALUES ('".$Notify->getID()."','".$Notify->getMessage()."','".$Notify->getUserID()."','".$Notify->getFromModule()."',".$Notify->getIsSeen().",".$Notify->getIsSent().")";
		$SQL = $this->_DB->doQuery($SQL);
		echo $SQL;

	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);

		return $Result;
	}

	//approve an issuance based on its id of the database
	//public function completeIssuance($Issuance){
	public function receiveIssuance($Issuance){


		$SQL = "UPDATE lms_issuance SET status = 'Received' WHERE id ='".$Issuance->getID()."'";
		$SQL= $this->_DB->doQuery($SQL);

		// Book++
		$SQL_Book = "UPDATE lms_books SET lms_books.availableCopies = lms_books.availableCopies+1 WHERE lms_books.id = '".$Issuance->getBookId()."'";
		$SQL_B = $this->_DB->doQuery($SQL_Book);

	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);

		return $Result;

	}

	//delete an issuance based on its id of the database
	public function deleteIssuance($Issuance){



		// Book++
		// if status =  completed, no need to increase

		$SQL_Book = "UPDATE lms_books,lms_issuance SET lms_books.availableCopies = lms_books.availableCopies+1 WHERE lms_issuance.status != 'Received' && lms_books.id = '".$Issuance->getBookId()."'";
		$SQL_B = $this->_DB->doQuery($SQL_Book);

		// after increasing, delete the issuance.
		$SQL = "DELETE from lms_issuance where id ='".$Issuance->getID()."'";
		$SQL = $this->_DB->doQuery($SQL);

	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);

		return $Result;

	}

	//read an user object based on its id form user object along with the Positions
	public function getIssuance($Issuance)
	{
		
		$SQL = "SELECT * FROM lms_issuance WHERE id = '".$Issuance->getID()."'";
		//echo $SQL;
		$this->_DB->doQuery($SQL);

		//reading all the rows 
			$row = $this->_DB->getTopRow();
			$this->_Issuance = new Issuance();

		 	$this->_Issuance->setID ( $row['id']);
		    $this->_Issuance->setBookId ( $row['bookId'] );   
		    $this->_Issuance->setIssuedTo( $row['issuedTo'] );
		    $this->_Issuance->setIssueDate( $row['issueDate'] );
		    //$this->_Issuance->setIssuedDate( $row['issuedDate'] );
		    $this->_Issuance->setReturnDate( $row['returnDate'] );
		    $this->_Issuance->setStatus( $row['status'] );
		    $this->_Issuance->setIssuedDate( $row['issuedDate'] );


			//todo: LOG util with level of log

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($this->_Issuance);

		return $Result;
	}

		// get all the issuance from the database using the database query
	public function getAllApprovedIssuance($LibraryId){

		$IssuanceList = array();

		$this->_DB->doQuery("SELECT lms_books.serialNo,lms_books.title,lms_books.author,lms_issuance.id as IssuanceID,lms_issuance.* FROM lms_issuance,lms_books,lms_shelf WHERE lms_issuance.bookId = lms_books.id && lms_books.shelfId = lms_shelf.id && lms_shelf.libraryId = '".$LibraryId."' ORDER BY lms_issuance.issuedDate DESC");

		$rows = $this->_DB->getAllRows();

		for($i = 0; $i < sizeof($rows); $i++) {
			$row = $rows[$i];
			$this->_Issuance = new Issuance();

		    $this->_Issuance->setID ( $row['IssuanceID']);
		    $this->_Issuance->setBookId ( $row['bookId'] );   
		    $this->_Issuance->setIssuedTo( $row['issuedTo'] );
		    $this->_Issuance->setIssueDate( $row['issueDate'] );
		    $this->_Issuance->setIssuedDate( $row['issuedDate'] );
		    $this->_Issuance->setReturnDate( $row['returnDate'] );
		    $this->_Issuance->setStatus( $row['status'] );
		

		    $IssuanceList[]=$this->_Issuance;
   
		}

		//todo: LOG util with level of log
		//echo '<br> log::complete getAllLibraries::'.print_r($IssuanceList);

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($IssuanceList);

		return $Result;
	}



	public function payReceived($Issuance){


		$SQL = "UPDATE lms_issuance SET status = 'Received' WHERE id ='".$Issuance->getID()."'";
		$SQL= $this->_DB->doQuery($SQL);

		// Book++
		//$SQL_Book = "UPDATE lms_books SET lms_books.availableCopies = lms_books.availableCopies+1 WHERE lms_books.id = '".$Issuance->getBookId()."'";
		//$SQL_B = $this->_DB->doQuery($SQL_Book);

	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);

		return $Result;

	}

}

//echo '<br> log:: exit the class.issuancedao.inc';

?>