<?php
include_once './util/class.util.inc';
include_once 'blade/view.books.blade.inc';
include_once './common/class.common.inc';
include_once './common/class.common.library.inc';
include_once './modules/library/bao/class.shelfbao.inc';
include_once './modules/library/bao/class.librarybao.inc';

$_ShelfBAO = new ShelfBAO();
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

 <!--Books Create, Edit formglobalBooks-->
 <br>
 <div class=" col-md-6 col-md-offset-3 col-sm-8 col-sm-offset-2">
 <div class="panel panel-info">
  <div class="panel-heading" align="center"><h3>Create New Books</h3></div>
  <div class="panel-body">
     <form  class="align-middle form-horizontal" method="POST" enctype="multipart/form-data">
      
         <span class="badge badge-success">Serial No</span>
         <input id="serialNo" type="text" class="form-control" name="serialNo" placeholder="Serial No" required value="<?php 
          if(isset($_GET['edit']))
           {
            echo $globalBooks->getSerialNo();
           }
          ?>">

          <span class="badge badge-success">Title</span>
         <input id="title" type="text" class="form-control" name="title" placeholder="Title of the Books" required value="<?php 
          if(isset($_GET['edit']))
           {
            echo $globalBooks->getTitle();
           }
          ?>">

          <span class="badge badge-success">Author</span>
         <input id="author" type="text" class="form-control" name="author" placeholder="Author of the Books" required value="<?php 
          if(isset($_GET['edit']))
           {
            echo $globalBooks->getAuthor();
           }
          ?>">


        <span class="badge badge-success">Select Shelf</span>
        <select class="form-control" id="sel1" name="shelfId">
        <?php
          if(isset($_GET['edit']))
           {
            $shelfSeleted = $globalBooks->getShelfId();

           }
           else
           {
             $shelfSeleted ="None";
           }

          // Conversion of LibrayId to Shelf Name
          // Finding librarina manually using userId
          $Library = $_ShelfBAO->getLibraryId($globalUserId)->getResultObject();
          $libraryId =  $Library->getID();  // LibraryId used to get allShelves
          //echo $libraryId."LibraryId";
          $librayIdArray =array('select'=>'Select a Shelf');
           $Result = $_ShelfBAO->getAllShelves($libraryId);
           if($Result->getIsSuccess())
           {
              $Libraries = $Result->getResultObject();
               $var = "";
               for ($i=0; $i < sizeof($Libraries); $i++) 
               { 
                  $Shelf = $Libraries[$i];
                  // From class.common.shelf.php
                  $id = $Shelf->getID();
                  $name = $Shelf->getName();

                  //array_push($librayIdArray, array($id => $name));
                  $temp[$id] = $name;
                  $librayIdArray = $temp;
                }

            }

          foreach ($librayIdArray as $key => $value) 
          {
            if( $shelfSeleted == $key)
            $t = "<option value=".$key." selected=\"selected\">".$value."</option>";
          else
            $t = "<option value=".$key.">".$value."</option>";

            echo $t ;
          }
        ?>
        </select>

        <span class="badge badge-success">Availabe Copies</span>
         <input id="availableCopies" type="number" class="form-control" name="availableCopies" placeholder="Available Copies of Books"  required value="<?php 
          if(isset($_GET['edit']))
           {
            echo $globalBooks->getAvailableCopies();
           }
          ?>">

        <?php
        //<span class="badge badge-success">Thumbnail</span>
        //  <input type="file" name="file" id="image">
        //<br>
        ?>



         <!--Thumbnail Src-->
        <div class="form-group">
            <div class="col-md-7">
                <input type="hidden" name="thumbnailsrc" id="thumbnailsrc" class="form-control" value="<?php
                    if(isset($_GET['edit'])) echo $globalBooks->getCover();?>">
            </div>
       </div>

        <!--Thumbnail-->
        <div class="form-group">
          <?php
           //<span class="badge badge-success">Thumbnail</span>
          ?> 
           <label for="thumbnail" class="control-label col-md-3">Thumbnail :</label>
             <div class="col-md-4">
                    <input type="file" name="thumbnail" onchange="previewImage(this);" id="thumbnail"<?php if (!isset($_GET['edit'])) echo ' required';?>>
              </div>
              <div class="col-md-1 thumbnail" id="divPreview" <?php if(!isset($_GET['edit'])) echo 'style="display: none"'; ?>>
                <img id="preview" src="<?php
                    if (isset($_GET['edit'])) echo $globalBooks->getCover();?>">
              </div>
        </div>

        <br>

        <input type="submit" name="<?php if(isset($_GET['edit'])) echo "update";
         else echo "save";?>" value="<?php if(isset($_GET['edit'])) echo "Update";
         else echo "Save";?>" class="btn btn-primary pull-right">
       </form>
  </div>
  </div>
</div>

<!--Books Search-->
<br><br>
 <div class=" col-md-6 col-md-offset-3 col-sm-8 col-sm-offset-2">
 <div class="panel panel-info">
  <div class="panel-heading" align="center"><h3>Search</h3></div>
  <div class="panel-body">
     <form  class="align-middle form-horizontal" name="search" method="GET">
      
        <input type="text" name="search" class="form form-control" placeholder="Enter Seach text..." required>
        <br>
        <input type="submit" value="Search" class="btn btn-primary pull-right">
       </form>
  </div>
  </div>
</div>
<!--Books Search end-->



<!--Books list-->

<div class="col-md-12">
<div class="panel panel-info">
  <div class="panel-heading" align="center"><h3>Books Information</h3></div>
  <div class="panel-body">
  
<div id="table">
    <table class="table">
        <thead>
              <tr id="books_list">
                <th >Serial No</th>
                
                <th >Title</th>
                <th >Author</th>
                <th >Shelf</th>
                <th >Available Copies</th>

                <th><img src="./resources/img/edit.ico" alt="Edit" height="40" weight = "40" class="table-img"></th>
                <th><img src="./resources/img/delete.png" alt="Delete" height="40" weight = "40" class="table-img"></th>
            </tr>
        </thead>
        <tbody>
           <?php
           $var = "";
            $Result = "";
           if(isset($_GET['shelf']))
           {
             $Books = new Books();
             $Books->setShelfID($_GET['shelf']);
             $Result = $_BooksBAO->getBooksByShelf($Books);

           }
           else if(isset($_GET['search']))
           {
              $Result = $_BooksBAO->searchBooks("%".$_GET['search']."%",$libraryId);

           }
           else
           {
            $Result = $_BooksBAO->getAllBooks($libraryId);

           }
           if($Result->getIsSuccess())
           {
              $Books = $Result->getResultObject();
            
               for ($i=0; $i < sizeof($Books); $i++) 
               { 
                  $Book = $Books[$i];
                  // Convert shelfId-> shelfName
                   $Shelf = new Shelf;
                   // Setting shelf object Id
                   $Shelf->setID($Book->getShelfId());
                   // Getting shelf object by id form shelfBao
                   $Result = $_ShelfBAO->getShelf($Shelf)->getResultObject();
                   // Getting shelf name by shelf object form class.common.shelf.php
                   $shelfName = $Result->getName();

                  // From class.common.books.php
                  $var .=  "<tr>";
                  $var .= "<td>".$Book->getSerialNo()."</td>";
                  //$var .= "<td>".$Book->getCover()."</td>";
                 
                  //$b = $Book->getCover();
                  //$var .= "<td>"."<img src="$b" alt="Icon" height="40" weight = "40" class="table-img">".$Book->getCover()."</td>";

                  $var .= "<td>".$Book->getTitle()."</td>";
                  $var .= "<td>".$Book->getAuthor()."</td>";
                  $var .= "<td>".$shelfName."</td>";
                  $var .= "<td>".$Book->getAvailableCopies()."</td>";
                  $var .= "<td > <a href='?edit=".$Book->getID()."'onclick='return confirmedit();'>Edit</a> </td>";
                  $var .= "<td > <a href='?delete=".$Book->getID()."'onclick='return confirmdelete();'>Delete</a> </td>";
                  
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
<!--Books list ends-->

<script>
   function confirmedit()
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
