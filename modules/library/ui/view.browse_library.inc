<?php
include_once './util/class.util.inc';
include_once 'blade/view.browse_library.blade.inc';
include_once './common/class.common.inc';
include_once './common/class.common.library.inc';
//include_once './common/class.common.paginate.inc';
include_once COMMON.'class.paginate.inc';
include_once './modules/library/bao/class.browse_librarybao.inc';
include_once './modules/library/bao/class.booksbao.inc';
include_once './modules/library/bao/class.shelfbao.inc';
include_once './modules/library/bao/class.librarybao.inc';
include_once './modules/user/bao/class.userbao.inc';

$_BooksBAO = new BooksBAO();
$_LibraryBAO = new LibraryBAO();
$_ShelfBAO = new ShelfBAO();
$_UserBAO = new UserBAO();

?>

<h1> <!-- Top Margin--> </h1>
<?php
if (!isset($_SESSION))
{
  session_start();  
}
if (isset($_SESSION['message']))
{
  $info= '<div class="alert alert-danger text-center h3">';
  $info.='<span>'.$_SESSION['message'].'</span>';
  $info.='</div>';
  echo $info;
  
  unset($_SESSION['message']);
}
?>
 <!--Browse_Library Create, Edit formglobalBrowse_Library-->
 <div class=" col-md-6 col-md-offset-3 col-sm-8 col-sm-offset-2">
 <div class="panel panel-info">
  <div class="panel-heading" align="center">Search</div>
  <div class="panel-body">
     <form  class="align-middle form-horizontal" name="searchFrom" method="GET">
      
        <input type="text" name="searchText" class="form form-control" placeholder="Enter Seach text..." required>
        <br>
        <input type="submit" value="Search" name="search" class="btn btn-primary pull-right">
       </form>
  </div>
  </div>
</div>


    <!--Browse_Library list-->
<div class="col-md-12">   
<div class="panel panel-info">
  <div class="panel-heading pull-right"><a href="<?php echo PageUtil::$LIBRARY_CHECKOUT;?>"><i class="glyphicon glyphicon-shopping-cart"></i>View Cart</a></div>

  <div class="panel-heading" align="center">Browse All Books</div>
  <div class="panel-body">



<!--Display all books card-->
<div class="container">
    <div class="row">

<!--Display items-->

      <?php
       $shelfName ="";
       $bookId ="";
       $title ="";
       $author ="";
       $cover = "";
       $availableCopies=0;
       $serialNo=0;
       $Result ="";
       if(isset($_GET['library_id']))
       {
          //$Result = $_BooksBAO->getAllBooks($_GET['library_id']);
          $a=20;
          //$_SESSION['libraryId'] = $_GET['library_id'];
          $results_per_page=4;
          $_Paginate=new Paginate();
          $Result=$_Paginate->loadPaginatedData($_Browse_LibraryBAO->getLibraryLimitBooks($_GET['library_id'],$_Paginate->paginationInitial(),$results_per_page));


       }
       elseif (isset($_GET['search']) && isset($_SESSION['libraryId']))
       {
          $Result = $_BooksBAO->searchBooks("%".$_GET['searchText']."%",$_SESSION['libraryId']);
          //echo $_SESSION['libraryId'].$_GET['searchText'];
       }
       else
       {
          //$Result = $_BooksBAO->getAllLibraryBooks();
          $a=10;
          $results_per_page=4;
          $_Paginate=new Paginate();
          $Result=$_Paginate->loadPaginatedData($_Browse_LibraryBAO->getLimitBooks($_Paginate->paginationInitial(),$results_per_page));

       }

       //if($Result->getIsSuccess())
       //{
       //       $Books = $Result->getResultObject();
            
       //        for ($i=0; $i < sizeof($Books); $i++) 
       foreach ($Result as $Book){
               //{ 
                  //$Book = $Books[$i];
                  // Convert shelfId-> shelfName
                   $Shelf = new Shelf;
                   // Setting shelf object Id
                   $Shelf->setID($Book->getShelfId());

                   // Getting shelf object by id form shelfBao
                   $ShelfResult = $_ShelfBAO->getShelf($Shelf)->getResultObject();
                   // Getting shelf name by shelf object form class.common.shelf.php
                   $shelfName = $ShelfResult->getName();

                   $Library = new Library();
                   $Library->setID($ShelfResult->getLibraryId());
                   $LibraryResult = $_LibraryBAO->getLibrary($Library)->getResultObject();
                   $LibraryName = $LibraryResult->getName();
                   //echo $LibraryName;

                   $bookId = $Book->getID();
                   $title = $Book->getTitle();
                   $author = $Book->getAuthor();
                   $availableCopies = $Book->getAvailableCopies();
                   $cover = $Book->getCover();
                   $serialNo = $Book->getSerialNo();

                   //if($cover==null)
                   //{
                   //  $cover = '3.jpg';
                   //}

              ?>
               <div class="col-md-3">
                 <div class="thumbnail">
                  <img height = "100" weight = "100" src="<?php echo $Book->getCover();?>"  alt="Books" >
                    <div class="caption">
                       <h4 class="pull-right"><i class="glyphicon glyphicon-book"></i> <?php echo $availableCopies; ?></h4>
                        <h4><?php echo $title; ?></h4>
                        <p>Author: <?php echo $author; ?></p>
                        <p>Serial No: <?php echo $serialNo; ?></p>
                        <p>Shelf: <?php echo $shelfName; ?></p>
                        <p>Library: <?php echo $LibraryName; ?></p>
                </div>
              
                <div class="space-ten"></div>

                <!--submit form add_to_cart-->
                <form class="align-middle form-horizontal" method="POST">
                  <input type="text" value="<?php echo $bookId;?>" name="bookId" style="display: none;">
                   <div class="btn-ground text-center">
                    <input type="submit" name="add_to_cart" class="btn btn-primary btn-block" value=" Add To Cart">
                
                   </div>
                </form>
               
                <div class="space-ten"></div>
               </div>
             </div>
             <?php
          }
          //if($i==0)
          //{
          //   echo "No books found!";
          //}
      //}
      ?>
<!--Display items end-->

      </div>

      <!--Pagination-->
      <?php
      if($a==10)
      {
        echo $_Paginate->paginate($results_per_page,PageUtil::$BROWSE,$_BooksBAO->getAllLibraryBooks());
      }
      if($a==20)
      {
      echo $_Paginate->paginate($results_per_page,PageUtil::$BROWSE,$_BooksBAO->getAllBooks($_GET['library_id']));
      }
      ?>


</div>
<!--Display all books card ends-->



</div>
</div>
</div>
<!--Browse_Library list ends-->

<script type="text/javascript" src="/wpl/resources/js/jquery.min.js"></script>


