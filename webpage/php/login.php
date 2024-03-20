<?php

//ini_set('display_errors', 1);
//ini_set('display_startup_errors', 1);
//error_reporting(E_ALL);

session_start(); // Start the session

// Retrieve the username and password from the POST request
$username = $_POST['username'];
$password = $_POST['password'];

$host = "localhost";
$port = 3306;
$database = "test";

// Store the database credentials in the session
$_SESSION['db_host'] = $host;
$_SESSION['db_port'] = $port;
$_SESSION['db_username'] = $username;
$_SESSION['db_password'] = $password;
$_SESSION['db_database'] = $database;

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

// Redirect to main.html
echo '<script>alert("Connection successful!");</script>';
echo '<script>window.location.href = "../main.html";</script>';
exit;
?>