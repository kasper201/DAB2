#include "driverinfo.h"
#include "getImage.h"
#include "htmlRequest.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <curl/curl.h>
#include <algorithm>

driverinfo::driverinfo()
{
}

driverinfo::~driverinfo()
{
}

int driverinfo::driver(int year,
                       std::vector<std::string> &givenNames, std::vector<std::string> &familyNames,
                       std::vector<std::string> &nationalities, std::vector<std::string> &permanentNumbers,
                       std::vector<std::string> &fullNames, std::vector<std::string> &driverIds,
                       std::map<std::string, std::vector<std::string>> &teamsIn) {
    this->year = year;
    std::string url = "https://ergast.com/api/f1/" + std::to_string(year) + "/drivers.json";
    std::string response = request.getRequest(url);
    std::cout << "Response: " << response << std::endl;

    // Correct JSON for readability
    std::string correctedJson = correctJson.correctJson(response);

    std::ofstream fileSave("tempDriver.json", std::ios::trunc);
    fileSave << correctedJson;
    fileSave.close();

    // Read JSON data from file
    std::ifstream file("tempDriver.json");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string jsonData = buffer.str();

    // Parse JSON
    std::istringstream stream(jsonData);
    while (stream) {
        std::string token;
        stream >> token;
        if (token == "\"givenName\":") {
            std::string givenName;
            stream >> std::quoted(givenName);
            givenNames.push_back(givenName);
        } else if (token == "\"familyName\":") {
            std::string familyName;
            stream >> std::quoted(familyName);
            familyNames.push_back(familyName);
        } else if (token == "\"nationality\":") {
            std::string nationality;
            stream >> std::quoted(nationality);
            nationalities.push_back(nationality);
        } else if(token == "\"permanentNumber\":") {
            std::string permanentNumber;
            stream >> std::quoted(permanentNumber);
            permanentNumbers.push_back(permanentNumber);
        } else if(token == "\"driverId\":") {
            std::string driverId;
            stream >> std::quoted(driverId);
            driverIds.push_back(driverId);
        }
    }

    for(int i = 0; i < familyNames.size(); i++) { // multithreading could make this faster
        getTeam(driverIds[i]);
        std::cout << "Team: " << teams[driverIds[i]][0] << std::endl;
    }

    teamsIn = this->teams;

    // Print names and nationalities
    for (size_t i = 0; i < givenNames.size(); ++i) {
        if(familyNames.empty() || givenNames.empty() || nationalities.empty() || permanentNumbers.empty() || driverIds.empty() || teams[driverIds[i]][0].empty())
            return 1;
        fullNames.push_back(givenNames[i] + " " + familyNames[i]);
        driverImage(familyNames[i]);
        //std::cout << i << " - Nationality: " << nationalities[i] << " full name: " << fullNames[i] << " Permanent number: " << permanentNumbers[i] << " Team: " << teams[driverIds[i]][0] << std::endl;
    }

    return 0;
}

void driverinfo::getTeam(std::string driver) {
    std::replace(driver.begin(), driver.end(), ' ', '_'); // Replace spaces with underscores
    std::string url = "http://ergast.com/api/f1/drivers/" + driver + "/constructors.json"; // get the team of the driver and team country
    std::cout << "URL: " << url << std::endl;
    std::string response = request.getRequest(url); // get the response from the API
    std::cout << response << std::endl;

    // Correct JSON for readability
    std::string correctedJson = correctJson.correctJson(response);

    std::ofstream fileSave("tempDriverTeam.json", std::ios::trunc);
    fileSave << correctedJson;
    fileSave.close();

    // Read JSON data from file
    std::ifstream file("tempDriverTeam.json");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string jsonData = buffer.str();

    // Parse JSON
    std::istringstream stream(jsonData);
    while (stream) {
        std::string token;
        stream >> token;
        // Check for the "name" key within the "Constructors" object
        if (token == "\"name\":") {
            std::string team;
            stream >> std::quoted(team);
            teams[driver].push_back(team);
            std::cout << "Team: " << teams[driver].back() << std::endl;
        }
    }

//    for (size_t i = 0; i < teams[driver].size(); i++) {
//        std::cout << "Team: " << teams[driver][i] << std::endl;
//    };

    file.close();
    remove("tempDriverTeam.json");
}

int driverinfo::driverImage(std::string driver) {
    std::string url = "https://media.formula1.com/content/dam/fom-website/drivers/" + std::to_string(year) + "Drivers/" + driver + ".jpg.img.1920.medium.jpg/1708344264039.jpg";
    getImage image;
    image.getTheImage(url, driver);
    return 0;
}
