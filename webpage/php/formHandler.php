<?php
session_start(); // Start the session

if (isset($_POST['search'])) { // Check if the search value is set in the POST request
    $_SESSION['search'] = $_POST['search']; // Set the search value in the session
}

// Check which form was submitted and redirect to the appropriate page
switch ($_POST['formType']) {
    case 'season':
        header("Location: ../season.html");
        break;
    case 'race':
        header("Location: ../race.html");
        break;
    case 'circuit':
        header("Location: ../circuit.html");
        break;
    case 'driver':
        header("Location: ../driver.html");
        break;
}

exit;
?>