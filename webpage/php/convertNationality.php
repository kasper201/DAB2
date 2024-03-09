<?php

function getCountriesByLanguage($language) {
    // Make a request to the REST Countries API
    $response = file_get_contents("https://restcountries.com/v2/lang/{$language}");

    // Decode the JSON response
    $data = json_decode($response, true);

    // Check if there are any countries where the language is spoken
    if (!empty($data)) {
        $countryNames = array_column($data, 'name');
        return "Countries where {$language} is spoken: " . implode(', ', $countryNames);
    } else {
        return "No countries found where {$language} is spoken.";
    }
}

?>

