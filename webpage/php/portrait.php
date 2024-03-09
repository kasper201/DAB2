
<?php
$imagepath = "img/portrait.jpg";

header("Content-type: image/jpeg");

readfile($imagepath);
?>

