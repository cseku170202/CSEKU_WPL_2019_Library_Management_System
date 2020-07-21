<?php
include_once './util/class.util.inc';
include_once './common/class.common.library.inc';
include_once './modules/library/bao/class.booksbao.inc';
include_once './modules/library/bao/class.browse_librarybao.inc';

$_Books = new Books();
$_Browse_LibraryBAO = new Browse_LibraryBAO();
$_DB = DBUtil::getInstance();
$_Log= LogUtil::getInstance();


$globalBrowse_Library = "";
$globalUserId= "";

// User finding 
// Permission will be handled in xml permission
// We just use this user id
if(isset($_SESSION['globalUser']))
{
	$User = $_SESSION['globalUser'];
	$globalUserId = $User->getID();
	//echo $globalUserId."UserId";
}

if(isset($_POST['add_to_cart']))
{
	$Browse_Library = new Browse_Library();	
	$Browse_Library->setID(Util::getGUID());
	$Browse_Library->setBookId($_POST['bookId']);
	$Browse_Library->setUserID($globalUserId);
	$_Browse_LibraryBAO->addToCart($Browse_Library);

	$_SESSION['message'] = "Book added to cart!";
	header("Location:".PageUtil::$BROWSE);
}



//echo '<br> log:: exit blade.browse_library.inc';
$_Log->log(LogUtil::$DEBUG,"exit blade.browse_library.inc");

?>