<?php
// write dao object for each class
include_once './common/class.common.inc';
include_once './util/class.util.inc';

Class BooksDao{

	private $_DB;
	private $_Books;


	function BooksDao(){

		$this->_DB = DBUtil::getInstance();

	}

	// get all the books from the database using the database query
	public function getAllBooks($libraryId)
	{

		$BooksList = array();

		$this->_DB->doQuery("SELECT lms_books.*,lms_shelf.id as shelfId FROM lms_books,lms_shelf WHERE lms_books.shelfId = lms_shelf.id && lms_shelf.libraryId = '".$libraryId."'");

		$rows = $this->_DB->getAllRows();

		for($i = 0; $i < sizeof($rows); $i++) {
			$row = $rows[$i];
			$this->_Books = new Books();

		    $this->_Books->setID ( $row['id']);
		    $this->_Books->setSerialNo ( $row['serialNo'] );   
		    $this->_Books->setTitle ( $row['title'] );
		    $this->_Books->setAuthor( $row['author'] );
		    $this->_Books->setShelfId( $row['shelfId'] );
		    $this->_Books->setAvailableCopies( $row['availableCopies'] );
		    $this->_Books->setCover( $row['cover'] );
		    		
		    $BooksList[]=$this->_Books;
   
		}

		//todo: LOG util with level of log
		//echo '<br> log::complete getAllLibraries::'.print_r($BooksList);

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($BooksList);

		return $Result;
	}

	// Get books form all library if available copies>1
	public function getAllLibraryBooks()
	{

		$BooksList = array();

		$this->_DB->doQuery("SELECT lms_books.*,lms_shelf.id as shelfId FROM lms_books,lms_shelf WHERE lms_books.shelfId = lms_shelf.id && lms_books.availableCopies>1");

		$rows = $this->_DB->getAllRows();

		for($i = 0; $i < sizeof($rows); $i++) {
			$row = $rows[$i];
			$this->_Books = new Books();

		    $this->_Books->setID ( $row['id']);
		    $this->_Books->setSerialNo ( $row['serialNo'] );   
		    $this->_Books->setTitle ( $row['title'] );
		    $this->_Books->setAuthor( $row['author'] );
		    $this->_Books->setShelfId( $row['shelfId'] );
		    $this->_Books->setAvailableCopies( $row['availableCopies'] );
		    $this->_Books->setCover( $row['cover'] );
		

		    $BooksList[]=$this->_Books;
   
		}

		//todo: LOG util with level of log
		//echo '<br> log::complete getAllLibraries::'.print_r($BooksList);

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($BooksList);

		return $Result;
	}

	//create books funtion with the books object
	public function createBooks($Books){

		$ID=$Books->getID();
		$SerialNo=$Books->getSerialNo();
		$Title=$Books->getTitle();
		$Author=$Books->getAuthor();
		$ShelfId=$Books->getShelfId();
		$AvailableCopies=$Books->getAvailableCopies();
		$Cover=$Books->getCover();

	

		$SQL = "INSERT INTO lms_books VALUES('$ID','$SerialNo','$Title','$Author','$ShelfId','$AvailableCopies','$Cover')";


		//creating the books
		$SQL = $this->_DB->doQuery($SQL);


	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);

		return $Result;
	}


	//search a books object based on some criteria
	public function searchBooks($SearchText,$LibraryId){
		
		$BooksList = array();
		
		$SQL = "SELECT lms_books.id,lms_books.serialNo,lms_books.title,lms_books.author,lms_shelf.name,lms_books.shelfId,lms_books.availableCopies  FROM lms_books,lms_shelf WHERE lms_books.shelfId = lms_shelf.id && lms_shelf.libraryId = '$LibraryId' && (lms_books.serialNo LIKE '$SearchText' || lms_books.title LIKE '$SearchText' || lms_books.author LIKE '$SearchText' || lms_shelf.name LIKE '$SearchText')";


		$this->_DB->doQuery($SQL);
		
		$rows = $this->_DB->getAllRows();

		for($i = 0; $i < sizeof($rows); $i++) {
			$row = $rows[$i];
			$this->_Books = new Books();

		    $this->_Books->setID ( $row['id']);
		    $this->_Books->setSerialNo ( $row['serialNo'] );   
		    $this->_Books->setTitle ( $row['title'] );
		    $this->_Books->setAuthor( $row['author'] );
		    $this->_Books->setShelfId( $row['shelfId'] );
		    $this->_Books->setAvailableCopies( $row['availableCopies'] );

		    $BooksList[]=$this->_Books;
   
		}

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($BooksList);

		return $Result;
	}


	//update a books object 
	public function updateBooks($Books){

		$SQL = "UPDATE lms_books SET
			serialNo='".$Books->getSerialNo()."',
			title='".$Books->getTitle()."',
			author='".$Books->getAuthor()."',
			shelfId='".$Books->getShelfId()."',
			availableCopies='".$Books->getAvailableCopies()."'
			WHERE id='".$Books->getID()."'";


		//updating the books
		$SQL = $this->_DB->doQuery($SQL);

	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);
		return $Result;

	}



	//delete an books based on its id of the database
	public function deleteBooks($Books){


		$SQL_delete = "DELETE from lms_books where id ='".$Books->getID()."'";
		$SQL_delete = $this->_DB->doQuery($SQL_delete);

	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);

		return $Result;

	}
	//read an user object based on its id form user object along with the Positions
	public function getBooks($Books)
	{
		
		$SQL = "SELECT * FROM lms_books WHERE id = '".$Books->getID()."'";
		//echo $SQL;
		$this->_DB->doQuery($SQL);

		//reading all the rows 
			$row = $this->_DB->getTopRow();
			$this->_Books = new Books();

		 	$this->_Books->setID ( $row['id']);
		    $this->_Books->setSerialNo ( $row['serialNo'] );   
		    $this->_Books->setTitle ( $row['title'] );
		    $this->_Books->setAuthor( $row['author'] );
		    $this->_Books->setShelfId( $row['shelfId'] );
		    $this->_Books->setAvailableCopies( $row['availableCopies'] );


			//todo: LOG util with level of log

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($this->_Books);

		return $Result;
	}
	//read an user object based on its id form user object along with the Positions
	public function getBooksByShelf($Books)
	{
		
		$SQL = "SELECT * FROM lms_books WHERE shelfId = '".$Books->getShelfID()."'";
		$BooksList = array();

		$this->_DB->doQuery($SQL);

		$rows = $this->_DB->getAllRows();

		for($i = 0; $i < sizeof($rows); $i++) {
			$row = $rows[$i];
			$this->_Books = new Books();

		    $this->_Books->setID ( $row['id']);
		    $this->_Books->setSerialNo ( $row['serialNo'] );   
		    $this->_Books->setTitle ( $row['title'] );
		    $this->_Books->setAuthor( $row['author'] );
		    $this->_Books->setShelfId( $row['shelfId'] );
		    $this->_Books->setAvailableCopies( $row['availableCopies'] );
		    
		

		    $BooksList[]=$this->_Books;
   
		}

		//todo: LOG util with level of log
		//echo '<br> log::complete getAllLibraries::'.print_r($BooksList);

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($BooksList);

		return $Result;
	}







        //upload thesis thumbnails
    public function uploadThumbnail($Books)
    {
        $target_dir = './resources/img/thumbnails/';
        $target_file = $target_dir . basename($_FILES['thumbnail']['name']);
        $fileType = pathinfo($target_file, PATHINFO_EXTENSION);
        if (!empty($_FILES['thumbnail']['tmp_name'])) {
            $size = getimagesize($_FILES['thumbnail']['tmp_name']);
            $uploaded = 1;

            if ($size !== false) {
                //echo 'File is an image - '.$size['mime'].'.';
                $uploaded = 1;
            } else {
                echo '<br>File is not an image';
                $uploaded = 0;
            }

            if (file_exists($target_file)) {
                echo '<br>Sorry, file already exists';
                $uploaded = 0;
            }

            if ($_FILES['thumbnail']['size'] > 50000000000000) {
                echo '<br>Sorry, your file is too large';
                $uploaded = 0;
            }

            if ($fileType != 'jpg' && $fileType != 'png' && $fileType != 'jpeg' && $fileType != 'ico') {
                echo '<br>Sorry, only jpg, jpeg, png & ico files are allowed';
                $uploaded = 0;
            }
            // Check if $uploadOk is set to 0 by an error
            if ($uploaded == 0) {
                echo "<br>Sorry, your file was not uploaded.";
                // if everything is ok, try to upload file
            } else {
                if(isset($_POST['update'])){
                    $del_dir=$_POST['thumbnailsrc'];
                    unlink($del_dir);
                }
                if (move_uploaded_file($_FILES["thumbnail"]["tmp_name"], $target_dir.$Books->getTitle().'.'.$fileType)) {
                    $Upload = array();
                    //returns a boolean value
                    $Upload['uploaded'] = $uploaded;
                    //returns the directory of the uploaded file
                    $Upload['target_file'] = $target_dir.$Books->getTitle().'.'.$fileType;
                    return $Upload;
                } else {
                    echo "<br>Sorry, there was an error uploading your file.";
                }
            }
        } else {
            if (!isset($_POST['update'])){
                echo "<br>Cannot upload the image.<br>Check image size.";
            }else{
                $Upload['uploaded']=1;
                $Upload['target_file']=$_POST['thumbnailsrc'];
                return $Upload;
            }
        }
    }

    //delete thesis thumbnail
    public function deleteThumbnail($Books){
        $del_dir=$Books->getCover();
        unlink($del_dir);

        return true;
    }












}

//echo '<br> log:: exit the class.booksdao.inc';

?>