<?php

include_once './util/class.util.inc';
include_once './common/class.common.library.inc';
include_once './modules/library/bao/class.librarybao.inc';

$_LibraryBAO = new LibraryBAO();
$_DB = DBUtil::getInstance();
$_Log= LogUtil::getInstance();


$globalLibrary = "";

/* saving a new library account*/

if(isset($_POST['save']))
{
	 $Library = new Library();	

     $Library->setID(Util::getGUID());
     $Library->setName($_DB->secureInput($_POST['name']));
     $Library->setAddress($_DB->secureInput($_POST['address']));
     $Library->setType($_DB->secureInput($_POST['type']));
     $Library->setLibrarian($_DB->secureInput($_POST['librarian']));
     $Library->setReturnPolicy($_DB->secureInput($_POST['returnPolicy']));
     $Library->setMaxIssuance($_DB->secureInput($_POST['maxIssuance']));

	$_LibraryBAO->createLibrary($Library);		
	header("Location:".PageUtil::$LIBRARY); 
}


/* deleting an existing library */

if(isset($_GET['delete']))
{

	$Library = new Library();	
	$Library->setID($_GET['delete']);	
	$_LibraryBAO->deleteLibrary($Library); //reading the library object from the result object

	header("Location:".PageUtil::$LIBRARY);
}

/*updating an existing library information*/

if(isset($_POST['update']))
{
	$Library = new Library();	

     $Library->setID($_DB->secureInput($_GET['edit']));
     $Library->setName($_DB->secureInput($_POST['name']));
     $Library->setAddress($_DB->secureInput($_POST['address']));
     $Library->setType($_DB->secureInput($_POST['type']));
     $Library->setLibrarian($_DB->secureInput($_POST['librarian']));
     $Library->setReturnPolicy($_DB->secureInput($_POST['returnPolicy']));
     $Library->setMaxIssuance($_DB->secureInput($_POST['maxIssuance']));
     

	$_LibraryBAO->updateLibrary($Library);

	header("Location:".PageUtil::$LIBRARY);
}
if(isset($_GET['edit']))
{
	$Library = new Library();
	$Library->setID($_GET['edit']);	
	$globalLibrary = $_LibraryBAO->getLibrary($Library)->getResultObject();

}

//echo '<br> log:: exit blade.library.inc';
$_Log->log(LogUtil::$DEBUG,"exit blade.library.inc");

?>