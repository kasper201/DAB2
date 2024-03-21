<?php
include 'getMySqli.php';

$mysqli = getMysqli();

// Retrieve the driver name from the POST request
$season = $mysqli->real_escape_string($_SESSION['year']);
$circuit = $mysqli->real_escape_string($_SESSION['search']);

$sql = "SELECT `First place` FROM race_view WHERE `season` = '$season' AND `circuit naam` = '$circuit'";
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

//    $row['selfie'] = base64_encode($row['selfie']);
    // Return circuit information as JSON
    header('Content-Type: application/json');
    echo json_encode($row);
}