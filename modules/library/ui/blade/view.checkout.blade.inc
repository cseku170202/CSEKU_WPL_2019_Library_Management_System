<?php
include_once './util/class.util.inc';
include_once './common/class.common.library.inc';
include_once './modules/library/bao/class.checkoutbao.inc';


$_CheckoutBAO = new CheckoutBAO();
$_DB = DBUtil::getInstance();
$_Log= LogUtil::getInstance();


$globalCheckout = "";
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

if(isset($_POST['checkout']))
{
	// No need to pass anything else an userId who is going to chechout
	// :-) because everithing is saved in cart 
    
	$_CheckoutBAO->completeCheckout($globalUserId);
	$_SESSION['message'] = 'Order placed successfully!';

	header("Location:".PageUtil::$LIBRARY_CHECKOUT);
}
if(isset($_GET['remove']))
{
	$Checkout = new Checkout();
	$Checkout->setID($_GET['remove']);
	$_CheckoutBAO->removeFromCart($Checkout);

	$_SESSION['message'] = 'Removed form cart!';

	header("Location:".PageUtil::$LIBRARY_CHECKOUT);
}



//echo '<br> log:: exit blade.browse_library.inc';
$_Log->log(LogUtil::$DEBUG,"exit blade.browse_library.inc");

?>