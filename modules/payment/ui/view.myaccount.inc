<?php
include_once './common/class.common.inc';
include_once 'blade/view.myaccount.blade.inc';
include_once './modules/payment/ui/view.due_fee.inc';
?>
<div class="panel panel-default">
<div class="panel-heading">Account Details </div>
<div class="panel-body">
<h1 class="hh1"> Account Details </h1>
<div class="aa">
Name: <?php echo $getROW->getFirstName(); ?>			<br>
Student id: <?php echo $getROW->getUniversityID(); ?><br>
Discipline: <?php echo $getROW->getDiscipline(); ?><br>
<b>Balance: <?php echo $getAccount->getAmount(); ?> </b> <br> <br>
</div>



<table class="table">
  <tr>
    <th>Due</th>
    <th>Date</th>
    <th>Type</th>
    <th>Payment</th>
  </tr>
   <?php
   $var = "";
  foreach ($PaymentDue as $result) {
  ?>
  <tr>
    <td><?php echo $result->getDue();?></td>
    <td><?php echo $result->getDate();?></td>
    <td><?php echo $result->getType();?></td>
    <?php
    $Type = $result->getType();
    $PID =  $result->getPID();
    ?>
    <?php
    //<td><a href="due_fee.php?type=<?php echo($Type); &pid=<?php echo($PID); ">Pay</a></td>
    $var = "<td > <a href='?due=".$result->getID()."'onclick='return;'>Pay</a> </td>";
    echo $var;
    ?>
  </tr>
  <?php

}?>
</table>

<br> <br> <br>


<table class="table">
  <tr>
    <th>Date</th>
    <th>Type</th>
    <th>Details</th>
  </tr>
   <?php
  foreach ($PaymentType as $result) {
  ?>
  <tr>
    <td><?php echo $result->getDate();?></td>
    <td><?php echo $result->getType();?></td>
    <?php 
    $Type =	$result->getType();
    $PID =  $result->getPID();
    if($Type == "Registration Fee")
    {?>
   	<td><a href="registration_feedetails.php?type=<?php echo($Type); ?>&pid=<?php echo($PID); ?>">View Details</a></td>
    <?php 
    }//closing first if condition
  if($Type == "Hall Fee")
  { //2nd if condition started here     ?>
 
      <td><a href="hall_feedetails.php?type=<?php echo($Type); ?>&pid=<?php echo($PID); ?>">View Details</a></td>
 
   <?php 
  }//2nd if closed

  if($Type == "Others Fee")
  {//3rd if started here ?>
    <td><a href="others_feedetails.php?type=<?php echo($Type); ?>&pid=<?php echo($PID); ?>">View Details</a></td>
  </tr>
  <?php
  }//3rd if closed here
}?>
</table>