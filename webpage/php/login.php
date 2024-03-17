<?php
session_start(); // Start the session

$host = "localhost";
$port = 3306;
$username = "root";
$password = ""; // This might be empty if your MySQL user doesn't require a password
$database = "test";

// Create a new database connection
$mysqli = new mysqli($host, $username, $password, $database, $port);

// Check if the connection was successful
if ($mysqli->connect_error) {
    // If the connection failed, redirect back to the login page with an error message
    $_SESSION['login_error'] = 'Failed to connect to MySQL: ' . $mysqli->connect_error;
    echo '<script>alert("Failed to connect to MySQL: ' . $mysqli->connect_error . '");</script>';
    echo '<script>window.location.href = "../login.html";</script>';
    exit;
}

// If the connection was successful, store the connection object in the session
$_SESSION['db_connection'] = $mysqli;

// Redirect to main.html
echo '<script>alert("Connection successful!");</script>';
echo '<script>window.location.href = "../main.html";</script>';
exit;
?>
