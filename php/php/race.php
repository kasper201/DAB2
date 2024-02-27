<?php

$servername = "your_mysql_server"; // Replace with your MySQL server name
$username = "your_username";       // Replace with your MySQL username
$password = "your_password";       // Replace with your MySQL password
$database = "your_database";       // Replace with your MySQL database name

// Create connection
$conn = new mysqli($servername, $username, $password, $database);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Assuming you have a table named 'circuits' with columns 'name', 'location', 'country'
$sql = "SELECT name, location, country FROM circuits LIMIT 1";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // Fetch the first row
    $row = $result->fetch_assoc();

    // Return circuit information as JSON
    header('Content-Type: application/json');
    echo json_encode($row);
} else {
    echo "No circuit information found.";
}

// Close the connection
$conn->close();

