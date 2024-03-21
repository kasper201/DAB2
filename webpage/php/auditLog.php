<?php
include 'getMySqli.php';

$mysqli = getMysqli();

$sql = "SELECT * FROM audit_log";
$result = $mysqli->query($sql);

if ($mysqli->error) {
    error_log("SQL error: " . $mysqli->error);
    http_response_code(500);
    echo "SQL error: " . $mysqli->error;
    exit;
}

$logs = [];
while ($row = $result->fetch_assoc()) {
    $logs[] = $row;
}

header('Content-Type: application/json');
echo json_encode($logs);
?>