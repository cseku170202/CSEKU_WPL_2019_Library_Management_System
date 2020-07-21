<?php
// write dao object for each class
include_once './common/class.common.inc';
include_once './util/class.util.inc';
include_once './modules/library/bao/class.issuancebao.inc';
include_once './modules/library/bao/class.librarybao.inc';

$_IssuanceBAO = new IssuanceBAO();
$_LibraryBAO = new LibraryBAO();

Class CheckoutDao{

	private $_DB;
	private $_Checkout;


	function CheckoutDao(){

		$this->_DB = DBUtil::getInstance();

	}

	// get all the items in cart from the database using the database query
	public function getCart($UserId)
	{

		$CheckoutList = array();

		$this->_DB->doQuery("SELECT lms_cart.*,lms_library.name,lms_library.returnPolicy from lms_cart,lms_books,lms_library,lms_shelf WHERE lms_cart.bookId = lms_books.id && lms_books.shelfId = lms_shelf.id && lms_shelf.libraryId = lms_library.id && lms_cart.userId ='".$UserId."'");

		$rows = $this->_DB->getAllRows();

		for($i = 0; $i < sizeof($rows); $i++) {
			$row = $rows[$i];
			$this->_Checkout = new Checkout();

		    $this->_Checkout->setID ( $row['id']);
		    $this->_Checkout->setBookId ( $row['bookId'] );   
		    $this->_Checkout->setUserId( $UserId );	
		    $this->_Checkout->setLibraryName( $row['name'] );	
		    $this->_Checkout->setLibraryReturnPolicy( $row['returnPolicy'] );

		    $CheckoutList[]=$this->_Checkout;
   
		}

		//todo: LOG util with level of log
		//echo '<br> log::complete getAllLibraries::'.print_r($CheckoutList);

		$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($CheckoutList);

		return $Result;
	}


	//Remove form chekcout
	public function removeFromCart($Checkout){


		$SQL = "DELETE FROM lms_cart WHERE lms_cart.id = '".$Checkout->getID()."'";
		$SQL= $this->_DB->doQuery($SQL);

	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);

		return $Result;

	}


	public function completeCheckout($UserId){
		$_IssuanceBAO = new IssuanceBAO();
	    $d = "";
	    $count = 0;

		$this->_DB->doQuery("SELECT lms_library.returnPolicy from lms_cart,lms_books,lms_library,lms_shelf WHERE lms_cart.bookId = lms_books.id && lms_books.shelfId = lms_shelf.id && lms_shelf.libraryId = lms_library.id && lms_cart.userId ='".$UserId."'");

		$row=$this->_DB->getTopRow();
        
        //$this->_Term=new Term();
        $this->_Checkout = new Checkout();
        //$this->_Term->setID($row['ID']);
        $this->_Checkout->setLibraryReturnPolicy( $row['returnPolicy'] );

        
        $time = time();
		$currentDate = date('Y-m-d',$time);//application date

		//$returnDate =  date('Y-m-d', strtotime('+3 months'));


		//$returnDate =  date('Y-m-d', strtotime($currentDate.'+'.$row['returnPolicy'].'days'));

       
        $issuedDate = date("Y-m-d");

		// Data retrive from cart table
		$SQL_Retrive = "SELECT * FROM lms_cart WHERE userId ='".$UserId."'";
		$SQL= $this->_DB->doQuery($SQL_Retrive);

		$rows = $this->_DB->getAllRows();

		for($i = 0; $i < sizeof($rows); $i++)
		{
			// Insert into issuance 
			$count++;
			$row = $rows[$i];

			$Issuance = new Issuance();
			$Issuance->setID(Util::getGUID());
			$Issuance->setBookId($row['bookId']);
			$Issuance->setIssuedTo($UserId);
			$Issuance->setIssueDate($currentDate);
			$Issuance->setStatus('Pending');
			$Issuance->setIssuedDate($issuedDate);


			$_IssuanceBAO->createIssuance($Issuance);

			// Decrease book
			$SQL_Decrease = "UPDATE lms_books SET availableCopies = availableCopies-1 WHERE lms_books.id = '".$row['bookId']."'";
			$SQL= $this->_DB->doQuery($SQL_Decrease);
   
		}

		//Finally delete the cart
		$SQL_Delete = "DELETE FROM lms_cart WHERE userId ='".$UserId."'";
		$SQL= $this->_DB->doQuery($SQL_Delete);

	 	$Result = new Result();
		$Result->setIsSuccess(1);
		$Result->setResultObject($SQL);

		return $Result;

	}

}

//echo '<br> log:: exit the class.issuancedao.php';

?>