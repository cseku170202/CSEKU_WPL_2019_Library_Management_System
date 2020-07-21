<?php
include_once './util/class.util.inc';
include_once './common/class.common.library.inc';
include_once './modules/library/bao/class.booksbao.inc';



$_BooksBAO = new BooksBAO();
$_DB = DBUtil::getInstance();
$_Log= LogUtil::getInstance();


$globalBooks = "";
$globalUserId= "";

/* saving a new books account*/
if(isset($_POST['save']))
{

    /*


	// Upload imge first
	$temp = explode(".", $_FILES["file"]["name"]);
	$unique = round(microtime(true)) . '.' . end($temp);
	
	$name = $_FILES['image']['name'];
	$size = $_FILES['image']['size'];
	$type = $_FILES['image']['type'];
	$extension = strtolower(substr($name, strpos($name, '.')+1 ));
	$tmp_name = $_FILES['image']['tmp_name'];
	$error = $_FILES['image']['error'];

	$max_size = 2097152;
	if (isset($name)) {
		if(!empty($name))
		{
			$location = './modules/library/thumbnail/';
			if(($extension=='jpg' || $extension=='jpeg') && $type=='image/jpeg' && $size<=$max_size)
			{
				if(move_uploaded_file($tmp_name, $location.$unique.$name))
				{
					echo "File uploaded !";
				}
				else
				{
					echo "Error uploading file.";
				}
				
			}
		}
		else {
			echo "Choose jpg/jpeg file and must less than 2 MB.";
		}
	}


	*/


	 $Books = new Books();	

     $Books->setID(Util::getGUID());
     $Books->setSerialNo($_DB->secureInput($_POST['serialNo']));
     $Books->setTitle($_DB->secureInput($_POST['title']));
     $Books->setAuthor($_DB->secureInput($_POST['author']));
     $Books->setShelfId($_DB->secureInput($_POST['shelfId']));
     $Books->setAvailableCopies($_DB->secureInput($_POST['availableCopies']));
     //$Books->setCover($unique.$name);
     $UploadThumbnail=$_BooksBAO->uploadThumbnail($Books);

     //check if the thumbnail has been uploaded
     if($UploadThumbnail['uploaded']==1)
     {
            $Books->setCover($_DB->secureInput($UploadThumbnail['target_file']));
            $Result=$_BooksBAO->createBooks($Books);

            if($Result->getIsSuccess()){
                echo '<strong>'.$Result->getResultObject().'</strong>';
                header("Location:".PageUtil::$BOOKS);
            }
     }

	$_BooksBAO->createBooks($Books);		
	header("Location:".PageUtil::$BOOKS); 
}


/* deleting an existing books */
if(isset($_GET['delete']))
{

	$Books = new Books();	
	$Books->setID($_GET['delete']);	
	$_BooksBAO->deleteBooks($Books); //reading the books object from the result object

	header("Location:".PageUtil::$BOOKS);
}

/*updating an existing books information*/
if(isset($_POST['update']))
{
	$Books = new Books();	

     $Books->setID($_DB->secureInput($_GET['edit']));
     $Books->setSerialNo($_DB->secureInput($_POST['serialNo']));
     $Books->setTitle($_DB->secureInput($_POST['title']));
     $Books->setAuthor($_DB->secureInput($_POST['author']));
     $Books->setShelfId($_DB->secureInput($_POST['shelfId']));
     $Books->setAvailableCopies($_DB->secureInput($_POST['availableCopies']));


	$_BooksBAO->updateBooks($Books);

	header("Location:".PageUtil::$BOOKS);
}
if(isset($_GET['edit']))
{
	$Books = new Books();
	$Books->setID($_GET['edit']);	
	$globalBooks = $_BooksBAO->getBooks($Books)->getResultObject();

}
// Librarian finding 
// Permission will be handled in xml permission
// We just use this user id as a librarian as only librarian has the access 
if(isset($_SESSION['globalUser']))
{
	$User = $_SESSION['globalUser'];
	// This will help to find the libraryId inseted into shelf.libraryId
	$globalUserId = $User->getID();
	//echo $globalUserId."UserId";
}
//echo '<br> log:: exit blade.books.inc';
$_Log->log(LogUtil::$DEBUG,"exit blade.books.inc");

?>