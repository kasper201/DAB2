<?php
include "getMySqli.php";
include "getArr.php";

$mysqli = getMysqli();

$query = "SELECT * FROM coureur_view ORDER BY naam DESC;";

$drivers = getArr($query, $mysqli);

header('Content-Type: application/json');  // Set the Content-Type header
echo json_encode($drivers);
return $drivers;