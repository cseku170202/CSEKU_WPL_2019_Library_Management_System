<?php
include_once './util/class.util.inc';
include_once './common/class.common.inc';
include_once './common/class.common.library.inc';
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

<h3> <!-- Top Margin--> </h3>
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
<section style="background-color: silver;" id="Statistics">
<div class='col-lg-12'>
	<!--Row 1-->
	<div class="row" id="row1">
		<?php
			$libraryBAO = new LibraryBAO;
			$Result = $libraryBAO->getAllLibraries();
			if($Result->getIsSuccess())
            {
            	$Libraries = $Result->getResultObject();
            	$data = "";
            	for ($i=0; $i < sizeof($Libraries); $i++) 
            	{ 
                	$Library = $Libraries[$i];
                	$data.='<div class="col-md-4 text-center">';
					$data.='<div class="panel alert-success">';
					$data.='<div class="text-box">';
					$data.='<p class="main-text h3">';
                	$data .='Name: '.$Library->getName();
					$data.='</p>';
					$data.='<p class="muted">';
                	$data .='Address: '.$Library->getAddress();
					$data.='</p>';
					$data.='<p class="muted">';
                	$data .='Librarian: '.$Library->getLibrarian();
					$data.='</p>';
					$data.='<p class="muted">';
                	$data .='<a href="browse_library.php?library_id='.$Library->getID().'">Enter <i class="glyphicon glyphicon-circle-arrow-right"></i></a>';
					$data.='</p>';
					$data.='</div>';
					$data.='</div>';
					$data.='</div>';
            	}
          	}
			echo $data;
		?>
		
	
	</div>
	<!--Row 1 end-->
</div>

</section>