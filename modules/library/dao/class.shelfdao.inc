<?php
// write dao object for each class
include_once './common/class.common.inc';
include_once './util/class.util.inc';

Class ShelfDao{

	private $_DB;
	private $_Shelf;
	private $_Library;


	function ShelfDao(){

		$this->_DB = DBUtil::getInstance();

	}

	// get all the libraries from the database using the database query
	public function getAllShelves($LibraryId){

		$ShelfList = array();

		$this->_DB->doQuery("SELECT * FROM lms_shelf where lms_shelf.libraryId='".$LibraryId."'");

		$rows = $this->_DB->getAllRows();

		for($i = 0; $i < sizeof($rows); $i++) {
			$row = $rows[$i];
			$this->_Shelf = new Shelf();

		    $this->_Shelf->setID ( $row['id']);
		    $this->_Shelf->setName ( $row['name'] );   
		    $this->_Shelf->setCapacity ( $row['capacity'] );
		    $this->_Shelf->setLibraryId( $row['libraryId'] );
		

		    $ShelfList[]=$this->_Shelf;
   
		}

		//todo: LOG util with level of log
		//echo '<br> log::complete getAllLibraries::'.print_r($ShelfList);

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($ShelfList);

		return $Result;
	}


	//create shelf funtion with the shelf object
	public function createShelf($Shelf){

		$ID=$Shelf->getID();
		$Name=$Shelf->getName();
		$Capacity=$Shelf->getCapacity();
		$LibraryId=$Shelf->getLibraryId();
	

		$SQL = "INSERT INTO lms_shelf VALUES('$ID','$Name','$Capacity','$LibraryId')";


		//creating the shelf
		$SQL = $this->_DB->doQuery($SQL);


	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);

		return $Result;
	}


	//search a shelf object based on some criteria
	public function searchShelf($SearchField,$SearchText){
		

		$SQL = "SELECT * FROM lms_shelf  WHERE ".$SearchField." Like '$SearchText'";


		$this->_DB->doQuery($SQL);
		
		$rows = $this->_DB->getAllRows();

		for($i = 0; $i < sizeof($rows); $i++) {
			$row = $rows[$i];
			$this->_Shelf = new Shelf();

		    $this->_Shelf->setID ( $row['id']);
		    $this->_Shelf->setName ( $row['name'] );
		    $this->_Shelf->setCapacity ( $row['capacity'] );   
		    $this->_Shelf->setLibraryId ( $row['libraryId'] );

		    $ShelfList[]=$this->_Shelf;
   
		}

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($ShelfList);

		return $Result;
	}


	//update a shelf object 
	public function updateShelf($Shelf){

		$SQL = "UPDATE lms_shelf SET
			name='".$Shelf->getName()."',
			capacity='".$Shelf->getCapacity()."',
			libraryId='".$Shelf->getLibraryId()."'
			WHERE id='".$Shelf->getID()."'";


		//updating the shelf
		$SQL = $this->_DB->doQuery($SQL);

	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);
		return $Result;

	}



	//delete an shelf based on its id of the database
	public function deleteShelf($Shelf){


		$SQL_delete = "DELETE from lms_shelf where id ='".$Shelf->getID()."'";
		$SQL_delete = $this->_DB->doQuery($SQL_delete);

	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);

		return $Result;

	}
	//read an user object based on its id form user object along with the Positions
	public function getShelf($Shelf)
	{
		
		$SQL = "SELECT * FROM lms_shelf WHERE id = '".$Shelf->getID()."'";
		//echo $SQL;
		$this->_DB->doQuery($SQL);

		//reading all the rows 
			$row = $this->_DB->getTopRow();
			$this->_Shelf = new Shelf();
			$this->_Shelf->setID($row['id']);
			$this->_Shelf->setName($row['name']);
			$this->_Shelf->setCapacity($row['capacity']);
			$this->_Shelf->setLibraryId($row['libraryId']);


			//todo: LOG util with level of log

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($this->_Shelf);

		return $Result;
	}

	public function getLibraryId($UserId)
	{
		
		$SQL = "SELECT * FROM lms_library WHERE lms_library.librarian = '".$UserId."'";
		//echo $SQL;
		$this->_DB->doQuery($SQL);

		//reading all the rows 
			$row = $this->_DB->getTopRow();

			$this->_Library = new Library();

		    $this->_Library->setID ( $row['id']);
		    $this->_Library->setName ( $row['name'] );   
		    $this->_Library->setAddress ( $row['address'] );
		    $this->_Library->setType ( $row['type'] );
		    $this->_Library->setLibrarian ( $row['librarian'] );


			//todo: LOG util with level of log

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($this->_Library);

		return $Result;
	}




	public function getShelfByLibrary($Shelf)
	{
		
		$SQL = "SELECT * FROM lms_shelf WHERE libraryId = '".$Shelf->getLibraryID()."'";
		$ShelfList = array();

		$this->_DB->doQuery($SQL);

		$rows = $this->_DB->getAllRows();

		for($i = 0; $i < sizeof($rows); $i++) {
			$row = $rows[$i];
			$this->_Shelf = new Shelf();

		    $this->_Shelf->setID ( $row['id']);
		    $this->_Shelf->setName ( $row['name'] );   
		    $this->_Shelf->setCapacity ( $row['capacity'] );
		    $this->_Shelf->setLibraryId( $row['libraryId'] );
	
		    $ShelfList[]=$this->_Shelf;
   
		}

		//todo: LOG util with level of log
		//echo '<br> log::complete getAllLibraries::'.print_r($BooksList);

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($ShelfList);

		return $Result;
	}

}

//echo '<br> log:: exit the class.shelfdao.inc';

?>