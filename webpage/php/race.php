<?php

if(isset($_SESSION['db_connection']))
{
    $conn = $_SESSION['db_connection'];
} else {
    header("Location: ../login.html");
}

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT name, location, country FROM circuits LIMIT 1";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // Fetch the first row
    $row = $result->fetch_assoc();

    // Return circuit information as JSON
    header('Content-Type: application/json');
    echo json_encode($row);
} else {
    echo '<script>alert("no circuit info found");</script>';
    echo '<script>window.location.href = "../main.html";</script>';
}

// Close the connection
$conn->close();

