<?php
include 'getMySqli.php';

$mysqli = getMysqli();

// Retrieve the raceID from the session
$raceID = $mysqli->real_escape_string($_SESSION['raceID']);

error_log($raceID);

// Call the stored procedure
$sql = "CALL deleteResultaat('$raceID')";
$result = $mysqli->query($sql);

if ($mysqli->error) {
    error_log("SQL error: " . $mysqli->error);
    http_response_code(500);
    echo "SQL error: " . $mysqli->error;
    exit;
}

// Redirect to main.html
//header('Location: ../main.html');
//exit;

error_log($result);