<?php
include "getMySqli.php";

$mysqli = getMysqli();

$query = "SELECT * FROM season_overview ORDER BY season DESC;";

error_log("Executing query: " . $query);

$result = $mysqli->query($query);
error_log("Number of rows: " . $result->num_rows);

if ($mysqli->error) {
    error_log("SQL error: " . $mysqli->error); // Log the error
    http_response_code(500); // Send a 500 status code
    echo "SQL error: " . $mysqli->error;
    exit;
}

$products = array();

if ($result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {
        array_push($products, $row);
        error_log("Row: " . print_r($row, true));
    }
}

echo json_encode($products);

return $products;