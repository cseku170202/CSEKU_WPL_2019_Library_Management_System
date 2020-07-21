<?php
include_once './util/class.util.inc';
include_once 'blade/view.issuance.blade.inc';
include_once './common/class.common.inc';
include_once './common/class.common.library.inc';
include_once './modules/library/bao/class.issuancebao.inc';
include_once './modules/library/bao/class.booksbao.inc';
include_once './modules/library/bao/class.shelfbao.inc';
include_once './modules/library/bao/class.testbao.inc';
include_once './modules/library/bao/class.librarybao.inc';
include_once './modules/user/bao/class.userbao.inc';

$_BooksBAO = new BooksBAO();
$_ShelfBAO = new ShelfBAO();
$_UserBAO = new UserBAO();
$_FineBAO = new FineBAO();
$_LibraryBAO = new LibraryBAO();

?>

<style type="text/css">
  #attribute{
    margin-left: 4px;
  }

  #btnApply{
    padding: 7px 29px; margin-left: 28px; margin-top: 14px;
  }
</style>

<h1> <!-- Top Margin--> </h1>

 <!--Issuance Search-->
 <div class=" col-md-6 col-md-offset-3 col-sm-8 col-sm-offset-2">
 <div class="panel panel-info">
  <div class="panel-heading"align="center">Search</div>
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
  <div class="panel-heading" align="center">MY Issuance INFO</div>
  <div class="panel-body">
  
<div id="table">
    <table class="table">
        <thead>
              <tr id="issuance_list">
               <th >Serial No</th>
                <th >Book Title</th>
                <th >Author Name</th>
                <th >Application Date</th>
                <th >BookIssue Date</th>
                <th >Returnable Date</th>
                
                <th >Remaining Days</th>
                <th >Fine</th>
                <th >Librarian</th>
                <th>Status</th>
            </tr>
        </thead>
        <tbody>
           <?php
           $var = "";

           

           $Result = $_IssuanceBAO->getIssuanceByUserId($globalUserId);
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
                  $var .= "<td>".$ResultBooks->getAuthor()."</td>";
                  $var .= "<td>".$Issuance->getIssueDate()."</td>";
                  $var .= "<td>".$Issuance->getIssuedDate()."</td>";
                  $var .= "<td>".$Issuance->getReturnDate()."</td>";

                  

                $temp = $Issuance->getStatus();

              if($temp!="Received" and $temp!="Approved")
              {
                   //$diff = 0;
                   $var .= "<td>"."</td>";
              }   
                  
              if($temp=="Approved")
              { 
                  //Remaining Days
                  $time = time();
                  $currentDate = date('Y-m-d',$time);
                  $returnabledate = $Issuance->getReturnDate();

                  if($currentDate < $returnabledate)
                  {
                     $date1=date_create($currentDate);
                     $date2=date_create($returnabledate);
                     $diff=date_diff($date1,$date2);
                     $var .= "<td bgcolor='cyan'>".$diff->format("%a")."</td>";///date show kortese apatoto
                     
                  }
                  else
                  {
                    $diff=0;
                    $var .="<td>".$diff."</td>";
                  }
              }

              if($temp=="Received")
              {
                   $diff = 0;
                   $var .= "<td>".$diff."</td>";
              } 
                 
                  ///Calculation of Remaining Days End


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

                     //$var .= "<td>".$diff->format("%a")."</td>";///date show kortese apatoto
                     //if($temp=="Approved")
                     //{ 
                        $var .= "<td>".$fine."</td>";
                     //}  ///actually fine show korte hobee
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
                 
               

              //if($temp=="Received")
              //{
              //    $fine = 0;
              //    $var .= "<td>".$fine."</td>";
              //} 
              //end calculating fine
                  
              

                   $Shelf = new Shelf;
                   // Setting shelf object Id
                   $Shelf->setID($ResultBooks->getShelfId());

                   // Getting shelf object by id form shelfBao
                   $ShelfResult = $_ShelfBAO->getShelf($Shelf)->getResultObject();
                   // Getting shelf name by shelf object form class.common.shelf.php
                   $shelfName = $ShelfResult->getName();

                   $Library = new Library();
                   $Library->setID($ShelfResult->getLibraryId());
                   $LibraryResult = $_LibraryBAO->getLibrary($Library)->getResultObject();
                   //$LibraryName = $LibraryResult->getName();
                   $LibraryName = $LibraryResult->getLibrarian();
                   $var .= "<td>".$LibraryName."</td>";

                   
                   $temp = $Issuance->getStatus();

                   if($temp=="Received")
                   {
                      $rgb = "Returned";
                      $var .= "<td>".$rgb."</td>";
                   }
                   else
                   {
                      $var .= "<td>".$Issuance->getStatus()."</td>";
                   }


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

<script type="text/javascript" src="/wpl/resources/js/jquery.min.js"></script>
