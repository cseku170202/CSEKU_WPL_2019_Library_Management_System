<?php
include_once './util/class.util.inc';
include_once './common/class.common.library.inc';
include_once './modules/library/bao/class.issuancebao.inc';
//include_once './modules/library/ui/view.issuance.inc';
include_once './modules/library/bao/class.testbao.inc';
include_once MODULES_PAYMENT.'bao/class.paymentbao.inc';


$_IssuanceBAO = new IssuanceBAO();
$_PaymentBAO = new PaymentBAO();
$_FineBAO = new FineBAO();
$_DB = DBUtil::getInstance();
$_Log= LogUtil::getInstance();

$globalIssuance = "";
$globalUserId= "";
$toUser = '';
$globalUser = '';
$globalUser = $_SESSION["globalUser"];
$User = new User();

//calculate fine
if(isset($_GET['fine']))
{
    $Issuance = new Issuance();	
    $Issuance->setID($_GET['fine']);
    $result = $_IssuanceBAO->getIssuance($Issuance)->getResultObject();

    $Fine = new Fine();
    $Result = $_FineBAO->getLibraryFine();
    if($Result->getIsSuccess())
    {
        $Fine = $Result->getResultObject();
        $fi = $Fine->getUserFine(); 
    }   

    //echo $fi;
    $time = time();
    $currentDate = date('Y-m-d',$time);
    //echo $currentDate;
  
    $returnabledate = $result->getReturnDate();
    $status = $result->getStatus();
    //echo $returnabledate;

    if($currentDate > $returnabledate and $status=="Approved")
    {
        $date1=date_create($currentDate);
        $date2=date_create($returnabledate);
        $diff=date_diff($date1,$date2);
        $fine=$diff->format("%a")*$fi;
    }
    else
    {
        $fine = 0;
    }
}  
//end calculating fine

//$globalIssuance = "";
//$globalUserId= "";
//$toUser = '';


if(isset($_GET['approve']))
{

	$Issuance = new Issuance();	
	$Issuance->setID($_GET['approve']);
	$_IssuanceBAO->approveIssuance($Issuance);
	// Retrive userId
	$ResultUser = $_IssuanceBAO->getIssuance($Issuance)->getResultObject();
	$toUser = $ResultUser->getIssuedTo();
	// Notify
	$Notify = new Notify();
	$Notify->setID(Util::getGUID());
	$Notify->setMessage("Your issuance request has been approved. Collect your books from library.");
	$Notify->setUserId($toUser);
	$Notify->setFromModule("Library Management System");
	$Notify->setIsSeen(0);
	$Notify->setIsSent(0);

	$_IssuanceBAO->setNotification($Notify);
	header("Location:".PageUtil::$ISSUANCE);
}


if(isset($_GET['receive']))
{
	// Complete issuance + Books++
	$Issuance = new Issuance();	
	$Issuance->setID($_GET['receive']);

	// Books++
	$Result = $_IssuanceBAO->getIssuance($Issuance)->getResultObject();
	$Issuance->setBookID($Result->getBookId());
	
	// Finally
	//$_IssuanceBAO->completeIssuance($Issuance); 
	$_IssuanceBAO->receiveIssuance($Issuance); 

	// Retrive userId
	$ResultUser = $_IssuanceBAO->getIssuance($Issuance)->getResultObject();
	$toUser = $ResultUser->getIssuedTo();
	// Notify
	$Notify = new Notify();
	$Notify->setID(Util::getGUID());
	$Notify->setMessage("Your issuance has been discard form the list.");
	$Notify->setUserId($toUser);
	$Notify->setFromModule("Library Management System");
	$Notify->setIsSeen(0);
	$Notify->setIsSent(0);

	$_IssuanceBAO->setNotification($Notify);

	header("Location:".PageUtil::$ISSUANCE);
}


/* deleting an existing issuance */
if(isset($_GET['delete']))
{

	$Issuance = new Issuance();	
	$Issuance->setID($_GET['delete']);	
	
	// Books++
	$Result = $_IssuanceBAO->getIssuance($Issuance)->getResultObject();
	$Issuance->setBookID($Result->getBookId());

	$_IssuanceBAO->deleteIssuance($Issuance);

	header("Location:".PageUtil::$ISSUANCE);
}


//pay fine for a book to the payment section
if(isset($_GET['fine']))
{
	 $Total = $fine;
	 //echo $Total;

	 $Issuance = new Issuance();	
	 $Issuance->setID($_GET['fine']);
	
	 $ResultUser = $_IssuanceBAO->getIssuance($Issuance)->getResultObject();
	 $User = $ResultUser->getIssuedTo();
	
	 //echo $User;
	 //$getROW = $_PaymentBAO->getUserById($User)->getResultObject();
	 $User = new User();
	 $User->setID($ResultUser->getIssuedTo());
	 $getROW = $_PaymentBAO->getUserById($User)->getResultObject();
	 $email = $getROW->getEmail();
	 //echo $email;
	 $getAccount = $_PaymentBAO->getAccountDetails($getROW)->getResultObject();
     $balance = $getAccount->getAmount();
     $Discipline = $getROW->getDiscipline();
     $UID = $getROW->getUniversityID();
     $Batch =  intval($UID /10000);
     $name = $getROW->getFirstName();
     date_default_timezone_set("Asia/Dhaka");
     $date = date('Y/m/d');

     if($Total > $balance)
	 {
	 	header("Location: message.php");
	 }

	 else
	 {

	    $Others = new OthersFee();
	    $OID = Util::getGUID();
	    $Others->setID($OID);
        $Others->setUniversityID($UID);
        $Others->setBatch($Batch);
        $Others->setName($name);
        $Others->setEmail($email);
        $Others->setDate($date);
        $Others->setDiscipline($Discipline);
        $Others->setDescription("library");
	    $Others->setTotal($Total);
	    $_PaymentBAO->setOthersDuePayment($Others);

	    $_IssuanceBAO->payReceived($Issuance);

        
	    $Type = "Others Fee";
	 	 		date_default_timezone_set("Asia/Dhaka");
		$Date = date('Y/m/d h:i:s', time());
	    $PaymentType = new PaymentType();
	    $PaymentType->setID(Util::getGUID());
	    $PaymentType->setPID($OID);
	    $PaymentType->setUniversityID($UID);
	    $PaymentType->setType($Type);
	    $PaymentType->setDate($Date);
	    $_PaymentBAO->setPaymentType($PaymentType);
	    //header("Location: myaccount.php");
	    //header("Location:".PageUtil::$ISSUANCE);

        date_default_timezone_set("Asia/Dhaka");
		$Date = date('Y/m/d h:i:s', time());
        $type = "Library Fee";
	    $PaymentDue = new PaymentDue();
	    $PaymentDue->setID(Util::getGUID());
	    $PaymentDue->setPID($OID);
	    $PaymentDue->setUniversityID($UID);
	    $PaymentDue->setType($type);
	    $PaymentDue->setDate($Date);
        $PaymentDue->setDue($Total);
        $_PaymentBAO->setPaymentDue($PaymentDue);


        header("Location:".PageUtil::$ISSUANCE);

	    
	  }

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

//echo '<br> log:: exit blade.issuance.inc';
$_Log->log(LogUtil::$DEBUG,"exit blade.issuance.inc");

?>