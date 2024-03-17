//
// Created by flits on 3/4/24.
//

#include "Results.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

Results::Results() {
    date.clear();
    time.clear();
    driver.clear();
    position.clear();
    points.clear();
    type.clear();
    location.clear();
    fastestLapTime.clear();
    fastestLapNr.clear();
}

Results::~Results() {

}

int Results::results(int year, int race, std::vector<std::string> &dateAll, std::vector<std::string> &timeAll, std::vector<std::string> &driverAll,
                     std::vector<std::string> &positionAll, std::vector<std::string> &pointsAll, std::vector<std::string> &type,
                     std::vector<std::string> &location, std::vector<std::string> &fastestLapTimeAll, std::vector<std::string> &fastestLapNrAll) {
    std::string url = "http://ergast.com/api/f1/" + std::to_string(year) + "/" + std::to_string(race) + "/results.json";
    std::string response = request.getRequest(url);
    std::cout << "Response: " << response << std::endl;

    // Correct JSON for readability
    std::string correctedJson = correctJson.correctJson(response);

    std::ofstream fileSave("tempResults.json", std::ios::trunc);
    fileSave << correctedJson;
    fileSave.close();

    // Read JSON data from file
    std::ifstream file("tempResults.json");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string data = buffer.str();

    // Parse JSON
    std::istringstream stream(data);
    bool firstTime = true; // the time at which the race takes place can now be recorded
    while(stream)
    {
        std::string token;
        stream >> token;
        if(token == "\"date\":") {
            std::string dateName;
            stream >> std::quoted(dateName);
            date.push_back(dateName);
        } else if(token == "\"time\":") {
            std::string timeName;
            stream >> std::quoted(timeName);
            if(!firstTime)
                time.push_back(timeName);
            firstTime = false;
        } else if(token == "\"permanentNumber\":") {
            std::string driverName;
            stream >> std::quoted(driverName);
            driver.push_back(driverName);
        } else if(token == "\"position\":") {
            std::string positionName;
            stream >> std::quoted(positionName);
            position.push_back(positionName);
        } else if(token == "\"points\":") {
            std::string pointsName;
            stream >> std::quoted(pointsName);
            points.push_back(pointsName);
        } else if(token == "\"lat\":") {
            std::string countryName;
            stream >> std::quoted(countryName);
            this->location.push_back(countryName);
            this->type.push_back("Normal");
        } else if(token == "\"FastestLap\":") {
            stream >> token;
            stream >> token;
            if(token == "\"rank\":") {
                stream >> token;
                stream >> token;
                if (token == "\"lap\":") {
                    std::string lap;
                    stream >> std::quoted(lap);
                    fastestLapNr.push_back(lap);
                    stream >> token;
                    stream >> token;
                    stream >> token;
                    stream >> token;
                    if (token == "\"time\":") {
                        std::string fastestLap;
                        stream >> std::quoted(fastestLap);
                        std::cout << "RaceNr: " << race << ", Fastest lap: " << fastestLap << std::endl;
                        fastestLapTime.push_back(fastestLap);
                    }
                }
            }
        }
    }
    if(getSprintResults(year, race) == 1) {
        std::cout << "No sprint results found" << std::endl;
    }

    while(fastestLapNr.size() < points.size()) {
        fastestLapNr.push_back("NULL");
        fastestLapTime.push_back("NULL");
    }
    while(driver.size() < points.size()) {
        driver.push_back("NULL");
    }
    // transfer data to main
    dateAll = date;
    timeAll = time;
    driverAll = driver;
    positionAll = position;
    pointsAll = points;
    type = this->type;
    location = this->location;
    fastestLapTimeAll = fastestLapTime;
    fastestLapNrAll = fastestLapNr;

    return 0;
}

int Results::getSprintResults(int year, int race) {
    std::string url = "http://ergast.com/api/f1/" + std::to_string(year) + "/" + std::to_string(race) + "/sprint.json";
    std::string response = request.getRequest(url);
    std::cout << "Response: " << response << std::endl;

    // Correct JSON for readability
    std::string correctedJson = correctJson.correctJson(response);

    std::ofstream fileSave("tempSprint.json", std::ios::trunc);
    fileSave << correctedJson;
    fileSave.close();

    // Read JSON data from file
    std::ifstream file("tempSprint.json");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string data = buffer.str();

    // Parse JSON
    std::istringstream stream(data);
    bool firstTime = true;
    while(stream)
    {
        std::string token;
        stream >> token;
        if(token == "\"total\":") {
            std::string total;
            stream >> std::quoted(total);
            if(total == "0")
                return 1;
        } else if(token == "\"date\":") {
            std::string dateName;
            stream >> std::quoted(dateName);
            date.push_back(dateName);
        } else if(token == "\"time\":") {
            std::string timeName;
            stream >> std::quoted(timeName);
            if(!firstTime)
                time.push_back(timeName);
            firstTime = false;
        } else if(token == "\"driver\":") {
            std::string driverName;
            stream >> std::quoted(driverName);
            driver.push_back(driverName);
        } else if(token == "\"position\":") {
            std::string positionName;
            stream >> std::quoted(positionName);
            position.push_back(positionName);
        } else if(token == "\"points\":") {
            std::string pointsName;
            stream >> std::quoted(pointsName);
            points.push_back(pointsName);
        } else if(token == "\"lat\":") {
            std::string countryName;
            stream >> std::quoted(countryName);
            this->location.push_back(countryName);
            type.push_back("Sprint"); // blursed solution
        } else if(token == "\"FastestLap\":") {
            stream >> token;
            stream >> token;
            if(token == "\"rank\":") {
                stream >> token;
                stream >> token;
                if (token == "\"lap\":") {
                    stream >> token;
                    std::string lap;
                    stream >> std::quoted(lap);
                    fastestLapNr.push_back(lap);
                    stream >> token;
                    stream >> token;
                    stream >> token;
                    if (token == "\"time\":") {
                        std::string fastestLap;
                        stream >> std::quoted(fastestLap);
                        std::cout << "RaceNr: " << race << ", Fastest lap: " << fastestLap << std::endl;
                        fastestLapTime.push_back(fastestLap);
                    }
                }
            }
        }
    }
    return 0;
}
