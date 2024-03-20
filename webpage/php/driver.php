<?php

session_start(); // Start the session

// Retrieve the database credentials from the session
$host = $_SESSION['db_host'];
$port = $_SESSION['db_port'];
$username = $_SESSION['db_username'];
$password = $_SESSION['db_password'];
$database = $_SESSION['db_database'];

// Create a new database connection
$mysqli = new mysqli($host, $username, $password, $database, $port);

// Check if the connection was successful
if ($mysqli->connect_error) {
    http_response_code(500); // Send a 500 status code
    echo "Failed to connect to MySQL: " . $mysqli->connect_error;
    exit;
}

$sql = "select * from coureur_view where naam = 'Max Verstappen';";
$result = $mysqli->query($sql);
error_log("Number of rows: " . $result->num_rows); // Add this line

if (!$result) {
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

    $row['selfie'] = base64_encode($row['selfie']);
    // Return circuit information as JSON
    header('Content-Type: application/json');
    echo json_encode($row);
}