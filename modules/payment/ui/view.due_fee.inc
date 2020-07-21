<?php
include_once UTILITY.'class.util.inc';
include_once MODULES_PAYMENT.'bao/class.paymentbao.inc';
include_once './common/class.common.inc';
include_once './util/class.util.inc';

$_PaymentBAO = new PaymentBAO();
$_DB = DBUtil::getInstance();
//$this->_DB = DBUtil::getInstance();
$globalUser = '';
$globalUser = $_SESSION["globalUser"];
$User = new User();
$User->setID($globalUser->getID());
$getROW = $_PaymentBAO->getUserById($User)->getResultObject();
//getting email
$email = $getROW->getEmail();
$getAccount = $_PaymentBAO->getAccountDetails($getROW)->getResultObject();
$balance = $getAccount->getAmount();
//getting discipline
$Discipline = $getROW->getDiscipline();
//setting batch from university id
$UID = $getROW->getUniversityID();
//setting batch 
$Batch =  intval($UID /10000);
//setting name
$name = $getROW->getFirstName();

//$Total = $getROW->getTotal();
//getting current date
date_default_timezone_set("Asia/Dhaka");
$date = date('Y/m/d');



//echo $balance;
//echo $UID;
//echo $name;


if(isset($_GET['due']))
{

	$PaymentDue = new PaymentDue();	
	$PaymentDue->setID($_GET['due']);	
	$_PaymentBAO->setGiveFine($PaymentDue); 
    $ID = $_GET['due'];
    $Due_ID = $ID;

    //$_PaymentBAO->setFineZero($Due_ID);


    //$Due = $PaymentDue->getDue();
    //echo $Due;

     $SQL = "SELECT Due FROM pms_due WHERE ID='$ID'";
        $SQL = $_DB->doQuery($SQL);
        $row = $_DB->getTopRow();
        $Due = $row['Due'];

        //echo $balance;

        //echo $Due;
        $balance = $balance - $Due;

        //$_PaymentBAO->setFineZero($Due_ID);
        

         //$a = 0;
        //$SQL2 = "UPDATE pms_due SET Due ='$a' WHERE ID='$ID'";
         //$SQL2 = $_DB->doQuery($SQL2);
        //$row2 = $_DB->getTopRow();

        //echo $balance;

        $SQL3 = "UPDATE pms_recharge SET Amount ='$balance' WHERE Email='$email'";
         $SQL3 = $_DB->doQuery($SQL3);
        $row3 = $_DB->getTopRow();
        $newbalance = $row3['Amount'];



        $_PaymentBAO->setFineZero($Due_ID);



        
        $Others = new OthersFee();
        $OID = Util::getGUID();
        
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











        $Result = new Result();
        $Result->setIsSuccess(1);
        $Result->setResultObject($SQL);

        return $Result;

        //$ID = $_GET['due'];
        //echo $ID;


        //echo $newbalance;
        header("Location: myaccount.php");
    
	    //header("Location:".PageUtil::$PAYMENT_MYACCOUNT);
}





?>