<?php
include_once './util/class.util.inc';
include_once './common/class.common.library.inc';
include_once './modules/library/bao/class.testbao.inc';
include_once './modules/user/bao/class.userbao.inc';

//$_ShelfBAO = new ShelfBAO();
$_UserBAO = new UserBAO();
$_FineBAO = new FineBAO();
$_DB = DBUtil::getInstance();
$_Log= LogUtil::getInstance();


$globalCost = "";
$globalUserId = "";

/* saving a new userfine account*/
if(isset($_POST['save']))
{
	 $Fine = new Fine();	

     $Fine->setID(Util::getGUID());
     $Fine->setUserFine($_DB->secureInput($_POST['userFine']));
    //$Fine->setLibraryId($_DB->secureInput($_POST['libraryId']));
     //$Library = $_FineBAO->getLibraryId($globalUserId)->getResultObject();
     //$libraryId =  $Library->getID(); 
     //echo $libraryId;
 
	$_FineBAO->createUserFine($Fine);		
	header("Location:".PageUtil::$TEST); 
}


/* deleting an existing shelf */
if(isset($_GET['delete']))
{

	$Fine = new Fine();	
	$Fine->setID($_GET['delete']);	
	$_FineBAO->deleteUserFine($Fine); //reading the shelf object from the result object

	header("Location:".PageUtil::$TEST);
}

/*updating an existing shelf information*/
if(isset($_POST['update']))
{
	 $Fine = new Fine();	

     $Fine->setID($_DB->secureInput($_GET['edit']));
     $Fine->setUserFine($_DB->secureInput($_POST['userFine']));
     //$Fine->setLibraryId($_DB->secureInput($_POST['libraryId']));
  
	 $_FineBAO->updateUserFine($Fine);
	 header("Location:".PageUtil::$TEST);
}
if(isset($_GET['edit']))
{
	$Fine = new Fine();
	$Fine->setID($_GET['edit']);	
	$globalCost = $_FineBAO->getUserFine($Fine)->getResultObject();

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





//echo '<br> log:: exit blade.test.inc';
$_Log->log(LogUtil::$DEBUG,"exit blade.library_user_fine.inc");

?>