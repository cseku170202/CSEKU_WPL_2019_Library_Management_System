<?php
include_once './util/class.util.inc';
include_once 'blade/view.checkout.blade.inc';
include_once './common/class.common.inc';
include_once './common/class.common.library.inc';
include_once './common/class.common.user.inc';
include_once './modules/user/bao/class.userbao.inc';
include_once './modules/library/bao/class.booksbao.inc';


$_BooksBAO = new BooksBAO();
$_CheckoutBAO = new CheckoutBAO();

if (isset($_SESSION['message']))
{
  $info= '<div class="alert alert-info text-center">';
  $info.='<span>'.$_SESSION['message'].'</span>';
  $info.='</div>';
  echo $info;
  var_dump($info);
  unset($_SESSION['message']);
}
?>

 <!--Checkout list-->
<div class="col-md-12">
<div class="panel panel-info">
  <div class="panel-heading">Checkout List</div>
  <div class="panel-body">

  <div id="table">
    <table class="table">
        <thead>
              <tr id="checkout_list">
                <th >Serial No</th>
                <th >Title</th>
                <th >Author</th>
                <th >Library</th>
                <th class="text-right"> Remove</th>
            </tr>
        </thead>
        <tbody>
           <?php
           $var = "";
           $Result = $_CheckoutBAO->getCart($globalUserId);
           if($Result->getIsSuccess())
           {
              $Items = $Result->getResultObject();
            
               for ($i=0; $i < sizeof($Items); $i++) 
               { 
                  $Checkout = $Items[$i];

                  // Book data retrive
                  $Book = new Books();
                  $Book->setID($Checkout->getBookId());
                  $BookResult = $_BooksBAO->getBooks($Book)->getResultObject();
                  
                  // From class.common.checkout.php
                  $var .=  "<tr>";
                  $var .= "<td>".$BookResult->getSerialNo()."</td>";
                  $var .= "<td>".$BookResult->getTitle()."</td>";
                  $var .= "<td>".$BookResult->getAuthor()."</td>";
                  $var .= "<td>".$Checkout->getLibraryName()."</td>";
                  $b = $Checkout->getLibraryReturnPolicy();
                  //echo $b;
                  $var .= "<td class='text-right'> <a href='?remove=".$Checkout->getID()."'onclick='return;'><i class='glyphicon glyphicon-remove'></i></a> </td>";
                }
                echo $var;

            }

           ?>
        </tbody>
       
    </table>
    </div>

<!--Data submission form-->
<form method="POST">
    <input type="submit" name="checkout" value="Checkout" class="btn btn-primary">
</form>

</div>
</div>
</div>
<!--Checkout list ends-->
