<?php
include "getMySqli.php";
include "getArr.php";

$mysqli = getMysqli();

$query = "SELECT * FROM season_overview ORDER BY season DESC;";

$products = getArr($query, $mysqli);

echo json_encode($products);

return $products;