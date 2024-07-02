<?php
include 'getMySqli.php';

$mysqli = getMysqli();

// Retrieve the season and circuit name from the POST request
$season = $mysqli->real_escape_string($_SESSION['year']);
$circuit = $mysqli->real_escape_string($_SESSION['search']);
$type = $mysqli->real_escape_string($_SESSION['type']);

$sql = "SELECT * FROM race_view WHERE `season` = '$season' AND `circuit naam` = '$circuit' AND `race type` = '$_SESSION[type]'";
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
} else {
    error_log("No results found for season: " . $season);
    http_response_code(404); // Not Found
    echo json_encode(["error" => "No results found for season: " . $season]);
    exit; // Ensure the script ends after sending the response
}