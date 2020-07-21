<?php
include_once './util/class.util.inc';
include_once 'blade/view.test.blade.inc';
include_once './common/class.common.inc';
include_once './common/class.common.library.inc';
include_once './modules/library/bao/class.librarybao.inc';
include_once './modules/user/bao/class.userbao.inc';
include_once './modules/library/bao/class.testbao.inc';

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
     $Fine = new Fine();
     $Library = $_FineBAO->getLibraryId($globalUserId)->getResultObject(); 
     $libraryName = $Library->getName();
?>


 <div class="panel-heading " style="text-align: center; background-color: rgb(150,150,240);" ><h1><?php echo $libraryName ?></h1></div>






 <br> <br>
 <div class=" col-md-6 col-md-offset-3 col-sm-8 col-sm-offset-2">
 <div class="panel panel-info">
  <div class="panel-heading" align="center"><h3>Change User Fine Information</h3></div>
  <div class="panel-body">
     <form  class="align-middle form-horizontal" method="POST" enctype="multipart/form-data">
      
         <span class="badge badge-success">User Fine</span>
         <input id="userFine" type="text" class="form-control" name="userFine" placeholder="Fine per day" required value="<?php 
          if(isset($_GET['edit']))
          {
            echo $globalCost->getUserFine();
          }
          ?>">


          <!--Hidden LibraryId-->
          <input id="LibraryId" name="libraryId" style="display: none" value="<?php
          if(isset($_GET['edit']))
           {
            
            //echo $globalCost->getLibraryId();
           }
           else
           {
            // Finding librarina manually using userId
            $Library = $_FineBAO->getLibraryId($globalUserId)->getResultObject();
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


<div class="col-md-12">
<div class="panel panel-info">
  <div class="panel-heading" align="center"><h3>Fine Information</h3></div>
  <div class="panel-body">
  
<div id="table">
    <table class="table">
        <thead>
              <tr id="fine_list">
                 <th >Library Name</th>
                 <th >Fine Per Day</th>
                 <th><img src="./resources/img/edit.ico" alt="Edit" height="40" weight = "40" class="table-img"></th>
                <th><img src="./resources/img/delete.png" alt="Delete" height="40" weight = "40" class="table-img"></th>
            </tr>
        </thead>
        <tbody>
           <?php
           $var = "";
           $Fine = new Fine();

           $Library = $_FineBAO->getLibraryId($globalUserId)->getResultObject();
           $libraryId =  $Library->getID();
           //echo  $libraryId;

           //$result = $_FineBAO->getLibraryFine()->getResultObject();
           //$r = $result->getUserFine();
           //echo $r;

           $Result = $_FineBAO->getLibraryFine();
           if($Result->getIsSuccess())
           {
                  $Fine = $Result->getResultObject();

                  $var .=  "<tr>";
                  $var .= "<td>".$Library->getName()."</td>";
                  $var .= "<td>".$Fine->getUserFine()."</td>";


                  //$var .= "<td>".$Library->getName()."</td>";
                  //$var .= "<td>".$Fine->getLibraryId()."</td>";
                  $var .= "<td > <a href='?edit=".$Fine->getID()."'onclick='return confirmedit();'>Edit</a> </td>";
                  $var .= "<td > <a href='?delete=".$Fine->getID()."'onclick='return confirmdelete();'>Delete</a> </td>";
             
                echo $var;
            }

           ?>
        </tbody>
        <tfoot>
        
        </tfoot>
    </table>

</div>
</div>
</div>
</div>

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
