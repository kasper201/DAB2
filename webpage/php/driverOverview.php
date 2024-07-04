<?php
include "getMySqli.php";
include "getArr.php";
include "utf8ize.php";


$mysqli = getMysqli();
$query = "SELECT * FROM coureur_view ORDER BY naam ASC;";
$drivers = getArr($query, $mysqli);

header('Content-Type: application/json');

$drivers = utf8ize($drivers);
$json = json_encode($drivers);
if ($json === false) {
    error_log("JSON encoding error: " . json_last_error_msg());
    http_response_code(500);
    echo json_encode(["error" => "JSON encoding error: " . json_last_error_msg()]);
    exit;
}

echo $json;
