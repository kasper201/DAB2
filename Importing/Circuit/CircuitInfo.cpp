//
// Created by flits on 3/3/24.
//

#include "CircuitInfo.h"
#include "getImage.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>


CircuitInfo::CircuitInfo() {

}

CircuitInfo::~CircuitInfo() {

}

int CircuitInfo::circuit(int year, std::vector<std::string> &circuit, std::vector<std::string> &country, std::vector<std::string> &circuitLength) {
    std::string url = "https://ergast.com/api/f1/2023/circuits.json";
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

std::string CircuitInfo::findInHtml(std::string html) { // find the length of the circuit in the html page of the circuit on the F1 website in km
    std::string extracted_data;
    // Find the position of the starting and ending substrings
    size_t start_pos = html.find("<p class=\"misc--label\">Circuit Length</p>\n                                    <p class=\"f1-bold--stat\">");
    size_t end_pos = html.find("<span class=\"misc--label\">");

    // Check if both substrings are found
    if (start_pos != std::string::npos && end_pos != std::string::npos) {
        // Extract the data between the substrings
        extracted_data = html.substr(start_pos + sizeof("<p class=\"misc--label\">Circuit Length</p>\n                                    <p class=\"f1-bold--stat\">") - 1,
                                                  end_pos - (start_pos + sizeof("<p class=\"misc--label\">Circuit Length</p>\n                                    <p class=\"f1-bold--stat\">") - 1));

        std::cout << "Extracted data: " << extracted_data << std::endl;
    } else {
        std::cout << "Substrings not found in the input string." << std::endl;
    }
    return extracted_data;
}

std::string CircuitInfo::getF1CircuitName(int circuitNr, int year)
{
    std::string circuitName;
    std::string url = "https://www.formula1.com/en/racing/" + std::to_string(year) + ".html";
    std::string html = request.getRequest(url);
    //std::cout << "Response: " << html << std::endl;

    size_t start_pos = 0;
    size_t end_pos = 0;
    int i = 0;
    while(i <= circuitNr + 1) // + 1 because the first circuit is testing
    {
        start_pos = html.find("<a href=\"/en/racing/" + std::to_string(year) + "/", end_pos);
        end_pos = html.find(".html\"", start_pos);
        circuitName = html.substr(start_pos + sizeof("<a href=\"/en/racing/2023/") - 1, end_pos - (start_pos + sizeof("<a href=\"/en/racing/2023/") - 1)); // 2023 can be used here since it doesn't matter for the length
        i++;
    }

    return circuitName;
}

std::string CircuitInfo::findCircuitLength(int circuitNr, int year) {
    std::cout << "Circuit number: " << circuitNr << std::endl;
    std::string circuitName = getF1CircuitName(circuitNr, year);
    std::cout << "Circuit name: " << circuitName << std::endl;
    std::string circuitUrl = "https://www.formula1.com/en/racing/2023/" + circuitName + "/Circuit.html";
    std::string html = request.getRequest(circuitUrl);
    std::cout << "Circuit URL: " << circuitUrl << std::endl;

    return findInHtml(html);
}

int CircuitInfo::circuitImage(std::string circuit) {
    std::string url = "https://media.formula1.com/image/upload/f_auto/q_auto/v1677244985/content/dam/fom-website/2018-redesign-assets/Circuit%20maps%2016x9/" + circuit + "_Circuit.png.transform/7col/image.png";
    getImage image;
    image.getTheImage(url, circuit);
    return 0;
}