#include <iostream>
#include "Driver info/driverinfo.h" // MN OGEN AAAAA WAAROM HEB IK HIER EEN SPATIE IN DE DIR GEDAAN??!?!?!?!
#include "Circuit/CircuitInfo.h"
#include "results/Results.h"
#include "database/SaveToDB.h"
#include "countries/GetCountries.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

int getAmountOfRaces(int year) {
    std::string url = "https://ergast.com/api/f1/" + std::to_string(year) + ".json";
    htmlRequest request;
    std::string response = request.getRequest(url);
    CorrectJson correctJson;
    std::string correctedJson = correctJson.correctJson(response);
    std::ofstream fileSave("tempAmountOfRaces.json", std::ios::trunc);
    fileSave << correctedJson;
    fileSave.close();
    std::ifstream file("tempAmountOfRaces.json");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string data = buffer.str();
    std::istringstream stream(data);
    std::string token;
    int amountOfRaces = 0;
    while(stream) {
        stream >> token;
        if(token == "\"total\":") {
            std::string amount;
            stream >> std::quoted(amount);
            amountOfRaces = std::stoi(amount);
            break;
        }
    }
    return amountOfRaces;
}

int main() {
    driverinfo driverinfo;
    CircuitInfo circuitInfo;
    Results results;
    SaveToDB saveToDB;
    GetCountries countries;

    std::cout << countries.countryConverter("Netherlands") << std::endl;
    std::vector<std::string>    givenNames, familyNames, nationalities,
                                permanentNumbers, fullNames, driverIds,
                                circuit, country, circuitLength,
                                dateAll, time, driverAll, position,
                                points, type, location,
                                fastestLapTimeAll, fastestLapNrAll = {""};
    std::map<std::string, std::vector<std::string>> teams;
    int year = 2023;
    for(int i = 0; i + year <= 2024; i++){
        driverinfo.driver(year + i, givenNames, familyNames, nationalities, permanentNumbers, fullNames, driverIds, teams);
        circuitInfo.circuit(year + i, circuit, country, circuitLength);
        for(int j = 1; j <= getAmountOfRaces(year + i); j++) {
            results.results(year + i, j, dateAll, time, driverAll, position, points, type, location, fastestLapTimeAll, fastestLapNrAll);
            std::cout << "Sizes result" << fastestLapNrAll.size() << " " << fastestLapTimeAll.size() << " " << driverAll.size() << " " << points.size() << std::endl;
        }
    }

    saveToDB.saveToFile(givenNames, familyNames, nationalities, permanentNumbers, fullNames, driverIds, teams, circuit, country, circuitLength, dateAll, time, position, points, driverAll, type, fastestLapTimeAll, fastestLapNrAll);

    return 0;
}