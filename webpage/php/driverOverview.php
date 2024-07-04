<?php
include "getMySqli.php";
include "getArr.php";

$mysqli = getMysqli();

$query = "SELECT * FROM coureur_view ORDER BY naam DESC;";


$drivers = getArr($query, $mysqli);

error_log("Drivers: " . print_r($drivers, true));

header('Content-Type: application/json');
echo json_encode($drivers);
return $drivers;