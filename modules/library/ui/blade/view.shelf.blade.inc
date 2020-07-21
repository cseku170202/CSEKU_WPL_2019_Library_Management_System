<?php
include_once './util/class.util.inc';
include_once './common/class.common.library.inc';
include_once './modules/library/bao/class.shelfbao.inc';
include_once './modules/user/bao/class.userbao.inc';

$_ShelfBAO = new ShelfBAO();
$_UserBAO = new UserBAO();
$_DB = DBUtil::getInstance();
$_Log= LogUtil::getInstance();


$globalShelf = "";
$globalUserId = "";

/* saving a new shelf account*/
if(isset($_POST['save']))
{
	 $Shelf = new Shelf();	

     $Shelf->setID(Util::getGUID());
     $Shelf->setName($_DB->secureInput($_POST['name']));
     $Shelf->setCapacity($_DB->secureInput($_POST['capacity']));
     $Shelf->setLibraryId($_DB->secureInput($_POST['libraryId']));

	$_ShelfBAO->createShelf($Shelf);		
	header("Location:".PageUtil::$SHELF); 
}


/* deleting an existing shelf */
if(isset($_GET['delete']))
{

	$Shelf = new Shelf();	
	$Shelf->setID($_GET['delete']);	
	$_ShelfBAO->deleteShelf($Shelf); //reading the shelf object from the result object

	header("Location:".PageUtil::$SHELF);
}

/*updating an existing shelf information*/
if(isset($_POST['update']))
{
	$Shelf = new Shelf();	

     $Shelf->setID($_DB->secureInput($_GET['edit']));
     $Shelf->setName($_DB->secureInput($_POST['name']));
     $Shelf->setCapacity($_DB->secureInput($_POST['capacity']));
     $Shelf->setLibraryId($_DB->secureInput($_POST['libraryId']));

	$_ShelfBAO->updateShelf($Shelf);

	header("Location:".PageUtil::$SHELF);
}
if(isset($_GET['edit']))
{
	$Shelf = new Shelf();
	$Shelf->setID($_GET['edit']);	
	$globalShelf = $_ShelfBAO->getShelf($Shelf)->getResultObject();

}
// Librarian finding 
// Permission will be handled in xml permission
// We just use this user id as a librarian as only librarian has the access 
if(isset($_SESSION['globalUser']))
{
	$User = $_SESSION['globalUser'];
	// This will help to find the libraryId inseted into shelf.libraryId
	$globalUserId = $User->getID();
}




//echo '<br> log:: exit blade.shelf.inc';
$_Log->log(LogUtil::$DEBUG,"exit blade.shelf.inc");

?>