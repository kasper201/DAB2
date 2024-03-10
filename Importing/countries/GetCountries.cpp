//
// Created by flits on 3/10/24.
//

#include "GetCountries.h"
#include "CorrectJson.h"
#include "htmlRequest.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

GetCountries::GetCountries() {

}

GetCountries::~GetCountries() {

}

std::string GetCountries::countryConverter(std::string country) {
    CorrectJson correctJson;
    htmlRequest request;
    // Make a request to get country data from Rest Countries API
    std::string apiUrl = "https://restcountries.com/v3.1/all";
    std::string json = request.getRequest(apiUrl);

    // Correct JSON for readability
    std::string correctedJson = correctJson.correctJson(json);

    std::ofstream fileSave("tempCircuit.json", std::ios::trunc);
    fileSave << correctedJson;
    fileSave.close();

    // Read JSON data from file
    std::ifstream file("tempCircuit.json");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string data = buffer.str();

    // Parse JSON
    std::istringstream stream(data);

    std::string currentToken;
    std::string countryName;
    std::string femaleDemonyms;
    std::vector<std::string> countries;

    while (stream >> currentToken) {
        if (currentToken == "\"name\":") {
            stream >> currentToken; // move to the next token
            if (currentToken == "{") {
                // inside the "name" object
                while (stream >> currentToken) {
                    if (currentToken == "\"common\":") {
                        stream >> std::quoted(countryName);
                        countries.push_back(countryName);
                    } else if (currentToken == "\"demonyms\":") {
                        stream >> currentToken; // move to the next token
                        stream >> currentToken; // assume it's the start of demonyms object
                        if (currentToken == "{") {
                            // inside the "demonyms" object
                            while (stream >> currentToken) {
                                if (currentToken == "\"eng\":") {
                                    stream >> currentToken; // move to the next token
                                    stream >> currentToken; // assume it's the start of the "eng" object
                                    if (currentToken == "{") {
                                        // inside the "eng" object
                                        while (stream >> currentToken) {
                                            if (currentToken == "\"f\":") {
                                                stream >> currentToken; // move to the next token
                                                stream >> std::quoted(femaleDemonyms);
                                                for(const auto & countrie : countries) {
                                                    if(countrie == country) {
                                                        return femaleDemonyms;
                                                    }
                                                }
                                                break; // break from the "eng" object loop
                                            } else if (currentToken == "}") {
                                                // end of the "eng" object
                                                break;
                                            }
                                        }
                                    }
                                } else if (currentToken == "}") {
                                    // end of the "demonyms" object
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    std::cout << "Demonym not available for " << country << "." << std::endl;
    return "N/A";
}
