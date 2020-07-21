<?php

include_once 'blade/view.library.blade.inc';
include_once './common/class.common.inc';
include_once './common/class.common.library.inc';
include_once './common/class.common.user.inc';
include_once './modules/user/bao/class.userbao.inc';

?>

<h1> <!-- Top Margin--> </h1>

 <!--Library Create, Edit formglobalLibrary-->
 <div class=" col-md-6 col-md-offset-3 col-sm-8 col-sm-offset-2">
 <div class="panel panel-info">
  <div class="panel-heading" align="center"><h1 class="hh1">Create New Library</h1></div>
  <div class="panel-body">
     <form  class="align-middle form-horizontal" method="POST">
      
         <span class="badge badge-success">Name</span>
         <input id="name" type="text" class="form-control" name="name" placeholder="Name of the Library" required value="<?php 
           if(isset($_GET['edit']))
           {
               echo $globalLibrary->getName();
           }
           ?>">

         <span class="badge badge-success">Address</span>
         <input id="address" type="text" class="form-control" name="address" placeholder="Where it is located?"  required value="<?php 
           if(isset($_GET['edit']))
           {
               echo $globalLibrary->getAddress();
           }
           ?>">

        <span class="badge badge-success">Select Librarian</span>
        <select class="form-control" id="sel0" name="librarian">
        <?php
//===============================================================
           if(isset($_GET['edit']))
           {
               $librarianSelected = $globalLibrary->getLibrarian();
           }
           else
           {
               $librarianSelected ="None";
           }

           /// Find all the librarina using user module
           $_UserBAO = new UserBAO();
           $allUsers = $_UserBAO->getAllUsersOfRole('Librarian')->getResultObject();
           // Array to hold librarian data.
           $librarianArray = array();
           // Now extract the user information
           for ($i=0; $i < sizeof($allUsers); $i++)
           { 
              $User = $allUsers[$i];

              $userId = $User->getID();
              $universityId = $User->getUniversityID();
              $email = $User->getEmail();
              $fullName = $User->getFullName();
              $status =$User->getStatus();
              $isArchived =$User->getIsArchived();
              $isDeleted =$User->getIsDeleted();

              $librarianArray += array($userId=>$fullName);
            }


          foreach ($librarianArray as $key => $value) 
          {
            if( $librarianSelected == $value)
            $t = "<option value=".$key." selected=\"selected\">".$value."</option>";
            else
            $t = "<option value=".$key.">".$value."</option>";

            echo $t ;
          }
//===============================================================
        ?>
        </select>

        <span class="badge badge-success">Select Library type</span>
        <select class="form-control" id="sel1" name="type">
        <?php
          if(isset($_GET['edit']))
           {
            $typeSeleted = $globalLibrary->getType();
           }
           else
           {
             $typeSeleted ="None";
           }

          $typesArray = array('Public'=>'Public','Seminar'=>'Seminar','Personal'=>'Personal','Others'=>'Others');
          foreach ($typesArray as $key => $value) 
          {
            if( $typeSeleted == $value)
            $t = "<option value=".$value." selected=\"selected\">".$value."</option>";
            else
            $t = "<option value=".$value.">".$value."</option>";

            echo $t ;
          }
        ?>
        </select>

         <span class="badge badge-success">Return Policy</span>
         <input id="returnPolicy" type="text" class="form-control" name="returnPolicy" placeholder="Retun Policy(in days)" required value="<?php 
          if(isset($_GET['edit']))
           {
            echo $globalLibrary->getReturnPolicy();
           }
          ?>">

          <span class="badge badge-success">Max Issuance</span>
         <input id="maxIssuance" type="text" class="form-control" name="maxIssuance" placeholder="Maximum num of books" required value="<?php 
          if(isset($_GET['edit']))
           {
            echo $globalLibrary->getMaxIssuance();
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

    <!--Library list-->
    <br><br><br>
<div class="col-md-12">
<div class="panel panel-info">
  <div class="panel-heading" align="center" ><h1 class="hh1">Library Information</h1></div>
  <div class="panel-body">
  
<div id="table">
    <table class="table">
        <thead>
              <tr id="library_list">
                <th >Name</th>
                <th >Address</th>
                <th >Librarian Name</th>
                <th >Type</th>
                <th >Return Policy</th>
                <th >Max Issuance</th>
                <th><img src="./resources/img/edit.ico" alt="Edit" height="40" weight = "40" class="table-img"></th>
                <th><img src="./resources/img/delete.png" alt="Delete" height="40" weight = "40" class="table-img"></th>
            </tr>
        </thead>
        <tbody>
           <?php
           $var = "";
           $Result = $_LibraryBAO->getAllLibraries();
           if($Result->getIsSuccess())
           {
              $Libraries = $Result->getResultObject();
            
               for ($i=0; $i < sizeof($Libraries); $i++) 
               { 
                  $Library = $Libraries[$i];
                  // userId2UserName
                  $FullName ="";
                  $User = new User();
                  $User->setID($Library->getLibrarian());
                  $Result = $_UserBAO->readUser($User)->getResultObject();

                  $FullName = $Result->getFullName();
                  

                  // From class.common.library.php
                  $var .=  "<tr>";
                  $var .= "<td>".$Library->getName()."</td>";
                  $var .= "<td>".$Library->getAddress()."</td>";
                  $var .= "<td>".$FullName."</td>";
                  $var .= "<td>".$Library->getType()."</td>";
                  $var .= "<td>".$Library->getReturnPolicy()."</td>";
                  $var .= "<td>".$Library->getMaxIssuance()."</td>";
                  $var .= "<td > <a href='?edit=".$Library->getID()."'onclick='return confirmedit();'>Edit</a> </td>";
                  $var .= "<td > <a href='?delete=".$Library->getID()."'onclick='return confirmdelete();'>Delete</a> </td>";
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
<!--Library list ends-->

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

<?php
//<th class="text-right"> Delete</th>
//
?>