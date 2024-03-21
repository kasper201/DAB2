<?php
include 'getMySqli.php';

$mysqli = getMysqli();

// Retrieve the form data from the POST request
$ResultID = $mysqli->real_escape_string($_POST['ResultID']);
$RaceID = $mysqli->real_escape_string($_POST['RaceID']);
$score = $mysqli->real_escape_string($_POST['score']);
$best_lap = $mysqli->real_escape_string($_POST['best_lap']);
$coureur_id = $mysqli->real_escape_string($_POST['coureur_id']);
$position = $mysqli->real_escape_string($_POST['position']);
$achieved_in = $mysqli->real_escape_string($_POST['achieved_in']);

// Call the stored procedure
$sql = "CALL insertResultaat('$ResultID', '$RaceID', '$score', '$best_lap', '$coureur_id', '$position', '$achieved_in')";
if (!$mysqli->multi_query($sql)) {
    error_log("SQL error: " . $mysqli->error);
    http_response_code(500);
    echo "SQL error: " . $mysqli->error;
    exit;
}

// Redirect to main.html
header('Location: ../main.html');
exit;