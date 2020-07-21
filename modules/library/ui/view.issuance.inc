<?php
include_once './util/class.util.inc';
include_once 'blade/view.issuance.blade.inc';
include_once './common/class.common.inc';
include_once './common/class.common.library.inc';
include_once './modules/library/bao/class.issuancebao.inc';
include_once './modules/library/bao/class.booksbao.inc';
include_once './modules/library/bao/class.shelfbao.inc';
include_once './modules/library/bao/class.librarybao.inc';
include_once './modules/user/bao/class.userbao.inc';
include_once './modules/library/bao/class.testbao.inc';

$_BooksBAO = new BooksBAO();
$_ShelfBAO = new ShelfBAO();
$_UserBAO = new UserBAO();
$_LibraryBAO = new LibraryBAO();
$_FineBAO = new FineBAO();


?>


<style type="text/css">
  #attribute{
    margin-left: 4px;
  }

  #btnApply{
    padding: 7px 29px; margin-left: 28px; margin-top: 14px;
  }
</style>


<?php
    
          $var = "";
          // Conversion of LibrayId to Shelf Name
          // Finding librarina manually using userId
          $Library = $_ShelfBAO->getLibraryId($globalUserId)->getResultObject();
          $libraryId =  $Library->getID();  // LibraryId used to get allShelves
          //echo $libraryId."LibraryId";
           $Result = $_ShelfBAO->getAllShelves($libraryId);
           if($Result->getIsSuccess())
           {
              $Libraries = $Result->getResultObject();
            
               for ($i=0; $i < sizeof($Libraries); $i++) 
               { 
                  $Shelf = $Libraries[$i];
                  // Convert libraryId-> libraryName
                   $Library = new Library;
                   // Setting library object Id
                   $Library->setID($Shelf->getLibraryId());
                   // Getting library object by id form libraryBao
                   $Result = $_LibraryBAO->getLibrary($Library)->getResultObject();
                   // Getting library name by library object form class.common.library.php
                   $libraryName = $Result->getName(); 
                }
               
            }

?>

 <div class="panel-heading " style="text-align: center; background-color: rgb(150,150,240);" ><h1><?php echo $libraryName ?></h1></div>



<h3> <!-- Top Margin--> </h3>

 <!--Issuance Search-->
 <div class=" col-md-6 col-md-offset-3 col-sm-8 col-sm-offset-2">
 <div class="panel panel-info">
   <?php
   /*
   <div class="panel-heading pull-right"><a href="<?php echo PageUtil::$LIBRARY_FINE;?>"><i class="glyphicon glyphicon-shopping-cart"></i>View Cart</a></div>
   */
   ?>

  <div class="panel-heading" align="center"><h3>Search</h3></div>
  <div class="panel-body">
     <form  class="align-middle form-horizontal" name="search" method="GET">
      
        <input type="text" name="searchText" class="form form-control" placeholder="Enter Seach text..." required>
        <br>
        <input type="submit" value="Search" class="btn btn-primary pull-right">
       </form>
  </div>
  </div>
</div>

    <!--Issuance list-->
<div class="col-md-12">
<div class="panel panel-info">
  <div class="panel-heading" align="center"><h3>Issuance Information</h3></div>
  <div class="panel-body">
  
<div id="table">
    <table class="table">
        <thead>
              <tr id="issuance_list">
               <th >Serial No</th>
                <th >Title</th>
                <th >Author</th>
                <th >User Name</th>
                <th >Application Date</th>
                <th >BookIssue Date</th>
                <th >Returnable Date</th>
                <th >Current Fine</th>
                <th>Status:

                 <select onchange="this.options[this.selectedIndex].value && (window.location = '?sort='+this.options[this.selectedIndex].value);">

                    <?php
                    $statusArray =array('Pending'=>'Pending','Approved'=>'Approved','Received'=>'Received');
                    foreach ($statusArray as $key => $value) 
                    {
                      $t="";
                      if(isset($_GET['sort']) && $_GET['sort'] == $key)
                      {
                         $t = "<option value=".$key." selected=\"selected\">".$value."</option>";
                      }
                      else
                      {
                         $t = "<option value=".$key.">".$value."</option>";
                      }

                      echo $t ;
                    }
                    ?>

                  </select>
                </th>
                <th><img src="./resources/img/approve2.png" alt="Delete" height="40" weight = "40" class="table-img"></th>
                 <th><img src="./resources/img/lms.png" alt="Delete" height="40" weight = "40" class="table-img"></th>

                <th><img src="./resources/img/delete.png" alt="Delete" height="40" weight = "40" class="table-img"></th>
                <th><img src="./resources/img/receiveRepair.png" alt="Delete" height="40" weight = "40" class="table-img"></th>

            </tr>
        </thead>
        <tbody>
           <?php
           // Finding librarina manually using userId
          $Library = $_ShelfBAO->getLibraryId($globalUserId)->getResultObject();
          $libraryId =  $Library->getID();
         // echo "$libraryId";
           $var = "";

          /* Sorting by Status */
          $Result ="No";
          if(isset($_GET['sort']))
          {

            $Result = $_IssuanceBAO->sortIssuanceByStatus($libraryId,"status",$_GET['sort']);
           // var_dump($Result) ;
          }
          else if(isset($_GET['searchText']))
          {

            $Result = $_IssuanceBAO->searchIssuance($libraryId,"%".$_GET['searchText']."%");
          }
          else
          {
           $Result = $_IssuanceBAO->getAllIssuance($libraryId);
          }
           if($Result->getIsSuccess())
           {
              $Issuances = $Result->getResultObject();
              if($Issuances!=null) // This condition is very very important
              {
                for ($i=0; $i < sizeof($Issuances); $i++) 
                { 
                  $Issuance = $Issuances[$i];
                  // Convert bookId-> bookName
                   $Books = new Books;
                   // Setting book object Id
                   $Books->setID($Issuance->getBookId());
                   // Getting book object by id form bookBao
                   $ResultBooks = $_BooksBAO->getBooks($Books)->getResultObject();
                  
                   // Convert userId-> FullName
                   $User = new User;
                   // Setting user object Id
                   $User->setID($Issuance->getIssuedTo());
                   // Getting user object by id form userBAO
                   $ResultUsers = $_UserBAO->readUser($User)->getResultObject();
                  

                  // From class.common.issuance.php
                  $var .=  "<tr>";
                  $var .= "<td>".$ResultBooks->getSerialNo()."</td>";
                  $var .= "<td>".$ResultBooks->getTitle()."</td>";
                  $ta = $ResultBooks->getTitle();
                  $var .= "<td>".$ResultBooks->getAuthor()."</td>";
                  $var .= "<td>".$ResultUsers->getFullName()."</td>";
                  $var .= "<td>".$Issuance->getIssueDate()."</td>";
                  $var .= "<td>".$Issuance->getIssuedDate()."</td>";
                  $var .= "<td>".$Issuance->getReturnDate()."</td>";

                  //$returningdate = date("Y-m-d");
                  //$var .= "<td>".$returningdate."</td>"; 

                  //calculate fine
                  $temp = $Issuance->getStatus();

                  
                  if($temp!="Approved" and $temp!="Received")
                  {
                      $fine = 0;
                      $var .= "<td>"."</td>";
                  } 

                  if($temp=="Approved")
                  { 
                      $Fine = new Fine();
                      $Result = $_FineBAO->getLibraryFine();
                      if($Result->getIsSuccess())
                      {
                         $Fine = $Result->getResultObject();
                         $fi = $Fine->getUserFine(); 
                      }   


                      $time = time();
                      $currentDate = date('Y-m-d',$time);
  
                      $returnabledate = $Issuance->getReturnDate();

                      if($currentDate > $returnabledate)
                      {
                          $date1=date_create($currentDate);
                          $date2=date_create($returnabledate);
                          $diff=date_diff($date1,$date2);
                          $fine=$diff->format("%a")*$fi;

                          //$var .= "<td>".$diff->format("%a")."</td>";
                          //if($temp=="Approved"){
                             $var .= "<td>".$fine."</td>";
                          //}
                      }
                      else
                      {
                          $fine = 0;
                          $var .= "<td>".$fine."</td>";
                      }
                  } 

                  if($temp=="Received")
                  {
                      $fine = 0;
                      $var .= "<td>".$fine."</td>";
                  } 
                 
                  $var .= "<td>".$Issuance->getStatus()."</td>";
                  
                  $var .= "<td > <a href='?approve=".$Issuance->getID()."'onclick='return confirmapprove();'>Approve</a> </td>";
                  $var .= "<td > <a href='?receive=".$Issuance->getID()."'onclick='return confirmreceive();'>Receive</a> </td>";
                  $var .= "<td > <a href='?delete=".$Issuance->getID()."'onclick='return confirmdelete();'>Delete</a> </td>";
                  $var .= "<td > <a href='?fine=".$Issuance->getID()."'onclick='return confirmpayfine();'>PayFine</a> </td>";

          
                }
              }
              echo $var;
            }

           ?>
        </tbody>
        <tfoot>
            <!--tr>
                <td></td>
                <td>Total</td>
                <td>33</td>
            </tr-->
        </tfoot>
    </table>
</div>
</div>
</div>
</div>
<!--Issuance list ends-->

<script>
   function confirmapprove()
   {
      var x = confirm("Sure to Approve!!!");
      if(x==true)
      {
         return true;
      }
      else
      {
         return false;
      }
   }

   function confirmreceive()
   {
      var x = confirm("Sure to Receive!!!");
      if(x==true)
      {
         return true;
      }
      else
      {
         return false;
      }
   }   

   function confirmdelete()
   {
      var x = confirm("Sure to Delete!!!");
      if(x==true)
      {
         return true;
      }
      else
      {
         return false;
      }
   }  

  function confirmpayfine()
   {
      var x = confirm("Sure to Pay Fine For This User!!!");
      if(x==true)
      {
         return true;
      }
      else
      {
         return false;
      }
   }  
</script>



<script type="text/javascript" src="/wpl/resources/js/jquery.min.js"></script>

