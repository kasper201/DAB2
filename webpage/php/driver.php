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