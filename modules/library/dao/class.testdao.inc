<?php
// write dao object for each class
include_once './common/class.common.inc';
include_once './util/class.util.inc';
include_once './modules/library/dao/class.testdao.inc';

//$_FineBAO = new FineBAO();
Class FineDao{

	private $_DB;
	private $_Fine;
	private $_Library;
	//private $_FineBAO;
	//$_FineBAO = new FineBAO();


	function FineDao(){

		$this->_DB = DBUtil::getInstance();

	}



		
	public function getLibraryFine(){

		$this->_DB->doQuery("SELECT * FROM lms_fine where 1");

		$row=$this->_DB->getTopRow();
        
        $this->_Fine = new Fine();
        $this->_Fine->setID ( $row['id']);
        $this->_Fine->setUserFine( $row['fine'] );
        //$this->_Fine->setLibraryId( $row['libraryId'] );


		//todo: LOG util with level of log
		//echo '<br> log::complete getAllLibraries::'.print_r($LibraryList);

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($this->_Fine);

		return $Result;
	}




	//create shelf funtion with the shelf object
	public function createUserFine($Fine){

		$ID=$Fine->getID();
		$Fine=$Fine->getUserFine();
		//$_FineBAO = new FineBAO();
		//$LibraryId=$Fine->getLibraryId();
		//$Library = $_FineBAO->getLibraryId($globalUserId)->getResultObject();
        //$libraryId =  $Library->getID(); 
	

		$SQL = "INSERT INTO lms_fine(id,fine) VALUES('$ID','$Fine')";
		$SQL = $this->_DB->doQuery($SQL);

        /*
		$SQL_NEW = "UPDATE lms_fine SET
			libraryId='$libraryId'
			WHERE id='".$Fine->getID()."'";


		//updating the shelf
		$SQL = $this->_DB->doQuery($SQL_NEW);
        */

	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);

		return $Result;
	}




	//update a shelf object 
	public function updateUserFine($Fine){

		$SQL = "UPDATE lms_fine SET
			fine='".$Fine->getUserFine()."'
			WHERE id='".$Fine->getID()."'";


		//updating the shelf
		$SQL = $this->_DB->doQuery($SQL);

	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);
		return $Result;

	}



	//delete an shelf based on its id of the database
	public function deleteUserFine($Fine){


		$SQL_delete = "DELETE from lms_fine where id ='".$Fine->getID()."'";
		$SQL_delete = $this->_DB->doQuery($SQL_delete);

	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);

		return $Result;

	}
	//read an user object based on its id form user object along with the Positions
	public function getUserFine($Fine)
	{
		
		$SQL = "SELECT * FROM lms_fine WHERE id = '".$Fine->getID()."'";
		//echo $SQL;
		$this->_DB->doQuery($SQL);

		//reading all the rows 
			$row = $this->_DB->getTopRow();
			$this->_Fine = new Fine();
			$this->_Fine->setID($row['id']);
			$this->_Fine->setUserFine($row['fine']);
			//$this->_Shelf->setCapacity($row['capacity']);
			//$this->_Fine->setLibraryId($row['libraryId']);


			//todo: LOG util with level of log

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($this->_Fine);

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


}

//echo '<br> log:: exit the class.testdao.inc';

?>