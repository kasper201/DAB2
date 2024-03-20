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

$sql = "SELECT * FROM landCoureur WHERE coureurID = " . 33;
$result = $mysqli->query($sql);

if ($result->num_rows > 0) {
    // Fetch the first row
    $row = $result->fetch_assoc();

    // Return circuit information as JSON
    header('Content-Type: application/json');
    echo json_encode($row);
}