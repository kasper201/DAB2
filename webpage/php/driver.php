<?php
include 'getMySqli.php';

$mysqli = getMysqli();

// Retrieve the driver name from the POST request
$driver = $mysqli->real_escape_string($_SESSION['search']);

$sql = "SELECT * FROM coureur_view WHERE naam = '$driver'";
$result = $mysqli->query($sql);
error_log("Number of rows: " . $result->num_rows); // Add this line

if ($mysqli->error) {
    error_log("SQL error: " . $mysqli->error); // Log the error
    http_response_code(500); // Send a 500 status code
    echo "SQL error: " . $mysqli->error;
    exit;
}

if ($result->num_rows > 0) {
    // Fetch the first row
    $row = $result->fetch_assoc();

    foreach ($row as $key => $value) {
        if (is_null($value)) {
            $row[$key] = "N/A"; // replace with default value
        }
    }

    // Return circuit information as JSON
    header('Content-Type: application/json');
    echo json_encode($row);
}