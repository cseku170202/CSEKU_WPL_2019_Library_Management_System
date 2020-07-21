<?php
// write dao object for each class
include_once './common/class.common.inc';
include_once './util/class.util.inc';

Class LibraryDao{

	private $_DB;
	private $_Library;

	function LibraryDao(){

		$this->_DB = DBUtil::getInstance();

	}


	// get all the libraries from the database using the database query
	public function getAllLibraries(){

		$LibraryList = array();

		$this->_DB->doQuery("SELECT * FROM lms_library where 1");

		$rows = $this->_DB->getAllRows();

		for($i = 0; $i < sizeof($rows); $i++) {
			$row = $rows[$i];
			$this->_Library = new Library();

		    $this->_Library->setID ( $row['id']);
		    $this->_Library->setName ( $row['name'] );   
		    $this->_Library->setAddress ( $row['address'] );
		    $this->_Library->setType ( $row['type'] );
		    $this->_Library->setLibrarian ( $row['librarian'] );
		    $this->_Library->setReturnPolicy ( $row['returnPolicy'] );
		    $this->_Library->setMaxIssuance ( $row['maxIssuance'] );
		

		    $LibraryList[]=$this->_Library;
   
		}

		//todo: LOG util with level of log
		//echo '<br> log::complete getAllLibraries::'.print_r($LibraryList);

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($LibraryList);

		return $Result;
	}


	//create library funtion with the library object
	public function createLibrary($Library){

		$ID=$Library->getID();
		$Name=$Library->getName();
		$Address=$Library->getAddress();
		$Type=$Library->getType();
		$Librarian=$Library->getLibrarian();
		$ReturnPolicy=$Library->getReturnPolicy();
		$MaxIssuance=$Library->getMaxIssuance();
	

		$SQL = "INSERT INTO lms_library VALUES('$ID','$Name','$Address','$Type','$Librarian',$ReturnPolicy,$MaxIssuance)";


		//creating the library
		$SQL = $this->_DB->doQuery($SQL);


	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);

		return $Result;
	}


	//search a library object based on some criteria
	public function searchLibrary($SearchField,$SearchText){
		

		$SQL = "SELECT * FROM lms_library  WHERE ".$SearchField." Like '$SearchText'";


		$this->_DB->doQuery($SQL);
		
		$rows = $this->_DB->getAllRows();

		for($i = 0; $i < sizeof($rows); $i++) {
			$row = $rows[$i];
			$this->_Library = new Library();

		    $this->_Library->setID ( $row['id']);
		    $this->_Library->setName ( $row['name'] );
		    $this->_Library->setAddress ( $row['address'] );   
		    $this->_Library->setType ( $row['type'] );
		    $this->_Library->setLibrarian ( $row['librarian'] );
		     $this->_Library->setReturnPolicy ( $row['returnPolicy'] );
		    $this->_Library->setMaxIssuance ( $row['maxIssuance'] );


		    $LibraryList[]=$this->_Library;
   
		}

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($LibraryList);

		return $Result;
	}


	//update a library object 
	public function updateLibrary($Library){

		$SQL = "UPDATE lms_library SET
			name='".$Library->getName()."',
			address='".$Library->getAddress()."',
			type='".$Library->getType()."',
			librarian='".$Library->getLibrarian()."',
			returnPolicy='".$Library->getReturnPolicy()."',
			maxIssuance='".$Library->getMaxIssuance()."'
			WHERE id='".$Library->getID()."'";


		//updating the library
		$SQL = $this->_DB->doQuery($SQL);

	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);
		return $Result;

	}



	//delete an library based on its id of the database
	public function deleteLibrary($Library){


		$SQL_delete = "DELETE from lms_library where id ='".$Library->getID()."'";
		$SQL_delete = $this->_DB->doQuery($SQL_delete);

	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);

		return $Result;

	}
	//read an user object based on its id form user object along with the Positions
	public function getLibrary($Library)
	{
		
		$SQL = "SELECT * FROM lms_library WHERE id = '".$Library->getID()."'";
		//echo $SQL;
		$this->_DB->doQuery($SQL);

		//reading all the rows 
			$row = $this->_DB->getTopRow();
			$this->_Library = new Library();
			$this->_Library->setID($row['id']);
			$this->_Library->setName($row['name']);
			$this->_Library->setAddress($row['address']);
			$this->_Library->setType($row['type']);
		    $this->_Library->setLibrarian ( $row['librarian'] );
		    $this->_Library->setReturnPolicy ( $row['returnPolicy'] );
		    $this->_Library->setMaxIssuance ( $row['maxIssuance'] );

			//todo: LOG util with level of log

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($this->_Library);

		return $Result;
	}

}

//echo '<br> log:: exit the class.librarydao.inc';

?>