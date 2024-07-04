<?php
function utf8ize($mixed) {
if (is_array($mixed)) {
foreach ($mixed as $key => $value) {
$mixed[$key] = utf8ize($value);
}
} else if (is_string($mixed)) {
return utf8_encode($mixed);
}
return $mixed;
}