<?php
include_once UTILITY.'class.util.inc';
include_once MODULES_PAYMENT.'bao/class.paymentbao.inc';
$_PaymentBAO = new PaymentBAO();
$_DB = DBUtil::getInstance();

$globalUser = '';
$globalUser = $_SESSION["globalUser"];
$User = new User();
$User->setID($globalUser->getID());
//
$getROW = $_PaymentBAO->getUserById($User)->getResultObject();
//getting balance
$getAccount = $_PaymentBAO->getAccountDetails($getROW)->getResultObject();
//getting discipline 
$Discipline = $getROW->getDiscipline();
//setting batch from university id
$UID = $getROW->getUniversityID();
//setting name
$name = $getROW->getFirstName();
$PaymentType = $_PaymentBAO->getPaymentType($getROW)->getResultObject();
$PaymentDue = $_PaymentBAO->getPaymentDue($getROW)->getResultObject();

/*
if(isset($_GET['due']))
{

	$PaymentDue = new PaymentDue();	
	$PaymentDue->setID($_GET['due']);	
	$_PaymentBAO->setGiveFine($PaymentDue); //reading the library object from the result object

	header("Location:".PageUtil::$PAYMENT_MYACCOUNT);
}
*/
