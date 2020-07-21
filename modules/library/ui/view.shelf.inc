<?php
include_once './util/class.util.inc';
include_once 'blade/view.shelf.blade.inc';
include_once './common/class.common.inc';
include_once './common/class.common.library.inc';
include_once './modules/library/bao/class.librarybao.inc';

$_LibraryBAO = new LibraryBAO();
$_ShelfBAO = new ShelfBAO();


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
            
          //  $libraryName = $Library->getName();


?>


 <div class="panel-heading " style="text-align: center; background-color: rgb(150,150,240);" ><h1><?php echo $libraryName ?></h1></div>





<h1> <!-- Top Margin--> </h1>

 <!--Shelf Create, Edit formglobalShelf-->
 <div class=" col-md-6 col-md-offset-3 col-sm-8 col-sm-offset-2">
 <div class="panel panel-info">
  <div class="panel-heading" align="center"><h3>Create New Shelf</h3></div>
  <div class="panel-body">
     <form  class="align-middle form-horizontal" method="POST">
      
         <span class="badge badge-success">Name</span>
         <input id="name" type="text" class="form-control" name="name" placeholder="Name of the Shelf" required value="<?php 
          if(isset($_GET['edit']))
           {
            echo $globalShelf->getName();
           }
          ?>">

         <span class="badge badge-success">Capacity</span>
         <input id="capacity" type="number" class="form-control" name="capacity" placeholder="Capacity of Shelf"  required value="<?php 
          if(isset($_GET['edit']))
           {
            echo $globalShelf->getCapacity();
           }
          ?>">
          <!--Hidden LibraryId-->
          <input id="LibraryId" name="libraryId" style="display: none" value="<?php
          if(isset($_GET['edit']))
           {
            
            echo $globalShelf->getLibraryId();
           }
           else
           {
            // Finding librarina manually using userId
            $Library = $_ShelfBAO->getLibraryId($globalUserId)->getResultObject();
            echo $Library->getID();  // LibraryId
           }
            
          ?>">

        <br>
        <input type="submit" name="<?php if(isset($_GET['edit'])) echo "update";
         else echo "save";?>" value="<?php if(isset($_GET['edit'])) echo "Update";
         else echo "Save";?>" class="btn btn-primary pull-right">
       </form>
  </div>
  </div>
</div>

    <!--Shelf list-->
<div class="col-md-12">
<div class="panel panel-info">
  <div class="panel-heading" align="center"><h3>Shelf Information</h3></div>
  <div class="panel-body">
  
<div id="table">
    <table class="table">
        <thead>
              <tr id="shelf_list">
                <th>Name</th>
                <th>Shelf Capacity</th>
                <th>Library Name</th>
                <th><img src="./resources/img/edit.ico" alt="Edit" height="40" weight = "40" class="table-img"></th>
                <th><img src="./resources/img/delete.png" alt="Delete" height="40" weight = "40" class="table-img"></th>
            </tr>
        </thead>
        <tbody>
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
                 
                  // From class.common.shelf.php
                  $var .=  "<tr>";
                  $var .= "<td><a href='books.php?shelf=".$Shelf->getID()."'onclick='return;'>".$Shelf->getName()."</a></td>";
                  $var .= "<td>".$Shelf->getCapacity()."</td>";
                  $var .= "<td>".$libraryName."</td>";
                  
                  $var .= "<td > <a href='?edit=".$Shelf->getID()."'onclick='return confirmation();'>Edit</a> </td>";
                  $var .= "<td > <a href='?delete=".$Shelf->getID()."'onclick='return confirmdelete();'>Delete</a> </td>";
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
<!--Shelf list ends-->
<script>
   function confirmation()
   {
      var x = confirm("Sure to edit!!!");
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
      var x = confirm("Sure to delete!!!");
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
