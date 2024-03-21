<?php
include 'getMySqli.php';

$mysqli = getMysqli();

// Retrieve the season name from the POST request
$season = $mysqli->real_escape_string($_SESSION['search']);

$sql = "SELECT * FROM season_view WHERE season = $season";
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

    $row['coureur_foto'] = base64_encode($row['coureur_foto']);
    // Return circuit information as JSON
    header('Content-Type: application/json');
    echo json_encode($row);
}