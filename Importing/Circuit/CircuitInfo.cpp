//
// Created by flits on 3/3/24.
//

#include "CircuitInfo.h"
#include "getImage.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>


CircuitInfo::CircuitInfo() {

}

CircuitInfo::~CircuitInfo() {

}

int CircuitInfo::circuit(int year, std::vector<std::string> &circuit, std::vector<std::string> &country, std::vector<std::string> &circuitLength, std::vector<std::string> &LATlocation) {
    std::string url = "https://ergast.com/api/f1/" + std::to_string(year) + "/circuits.json";
    std::string response = request.getRequest(url);
//    std::cout << "Response: " << response << std::endl;

    // Correct JSON for readability
    std::string correctedJson = correctJson.correctJson(response);

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
    while(stream) { // iterate through the JSON data
        std::string token;
        stream >> token;
        if(token == "\"circuitId\":") {
            std::string circuitId;
            stream >> std::quoted(circuitId);
            circuit.push_back(circuitId);
            std::cout << "Circuit ID: " << circuitId << std::endl;
        } else if(token == "\"country\":") {
            std::string countryName;
            stream >> std::quoted(countryName);
            country.push_back(countryName);
            std::cout << "Country: " << countryName << std::endl;
        } else if(token == "\"lat\":") {
            std::string lat;
            stream >> std::quoted(lat);
            LATlocation.push_back(lat);
            std::cout << "Latitude: " << lat << std::endl;
        }
    }
    for(int i = 0; i < circuit.size(); i++) {
        circuitImage(getF1CircuitName(i, year));

        circuitLength.push_back(findCircuitLength(i, year));
    }

    for(int i = 0; i < circuit.size(); i++) {
        std::cout << "Circuit: " << circuit[i] << std::endl;
        std::cout << "Country: " << country[i] << std::endl;
        std::cout << "Circuit length: " << circuitLength[i] << std::endl;
    }

    return 0;
}

std::string CircuitInfo::findLengthInHtml(const std::string& response) { // find the length of the circuit in the html page of the circuit on the F1 website in km
    CorrectJson correctJson;
    std::string length;
    // Correct JSON for readability
    std::string correctedJson = correctJson.correctJson(response);

    std::ofstream fileSave("tempCircuitInfo.json", std::ios::trunc);
    fileSave << correctedJson;
    fileSave.close();

    // Read JSON data from file
    std::ifstream file("tempCircuitInfo.json");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string data = buffer.str();

    // Parse JSON
    std::istringstream stream(data);
    while(stream) { // iterate through the JSON data
        std::string token;
        stream >> token;
        if (token == R"(\"children\":)") {
            int j = 0;
            int counter = 0;
            do {
                counter++;
                stream >> token;
                if (token == R"(\"children\":)") {
                    j++;
                }
                if (token == R"(\"Circuit Length\")") {
                    break;
                }
                if(counter > 262144)
                    return "'N/A'";
            } while(j < 82);
            for(int i = 0; i < 1; i++) {
                stream >> token;
            }
            stream >> std::quoted(length);
            if (length.length() > 4) {
                length.erase(0, 2);
                length.erase(length.end() - 3, length.end());
            }
            std::cout << "length: " << length << std::endl;
            break;
        }
    }
    return length;
}

std::string CircuitInfo::getF1CircuitName(int circuitNr, int year)
{
    std::string circuitName;
    std::string url = "https://www.formula1.com/en/racing/" + std::to_string(year);
    std::string html = request.getRequest(url);

    std::string correctedJson = correctJson.correctJson(html);
    //std::cout << "URL: " << url << std::endl;
    //std::cout << "Circuit Response: " << html << std::endl;

    std::ofstream fileSave("tempCircuitInfo.json", std::ios::trunc);
    fileSave << correctedJson;
    fileSave.close();

    // Read JSON data from file
    std::ifstream file("tempCircuitInfo.json");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return "N/A";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string jsonData = buffer.str();

    // Parse JSON
    std::istringstream stream(jsonData);
    int i = 0;
    while (stream && i <= circuitNr+1) {
        std::string token;
        stream >> token;
        // Check for the "name" key within the "Constructors" object
        if (token == R"(\"meetingCountryName\":)") {
            i++;
            stream >> std::quoted(circuitName);
            if (circuitName.length() > 4) {
                circuitName.erase(0, 2);
                circuitName.erase(circuitName.end() - 3, circuitName.end());
            }
            std::transform(circuitName.begin(), circuitName.end(), circuitName.begin(), ::tolower);
            //std::cout << "circuitName: " << circuitName << std::endl;
        }
    }

    return circuitName;
}

std::string CircuitInfo::findCircuitLength(int circuitNr, int year) {
    std::cout << "Circuit number: " << circuitNr << std::endl;
    std::string circuitName = getF1CircuitName(circuitNr, year);
    std::cout << "Circuit name: " << circuitName << std::endl;
    std::string circuitUrl = "https://www.formula1.com/en/racing/2023/" + circuitName + "/circuit";
    std::string html = request.getRequest(circuitUrl);
    //std::cout << "html: " << html << std::endl;
    std::cout << "Circuit URL: " << circuitUrl << std::endl;
    return findLengthInHtml(html);
}

int CircuitInfo::circuitImage(std::string circuit) {
    std::cout << "Saving image of Circuit: " << circuit << std::endl;
    std::string url = "https://media.formula1.com/image/upload/f_auto/q_auto/v1677244985/content/dam/fom-website/2018-redesign-assets/Circuit%20maps%2016x9/" + circuit + "_Circuit.png.transform/7col/image.png";
    getImage image;
    image.getTheImage(url, circuit);
    return 0;
}