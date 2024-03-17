//
// Created by flits on 3/9/24.
//

#include "SaveToDB.h"
#include "../countries/GetCountries.h"

#include <iostream>
#include <fstream>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define MIN(a, b) ((a) < (b) ? (a) : (b))

SaveToDB::SaveToDB() {

}

SaveToDB::~SaveToDB() {

}

/**
 *
 * @param givenNames
 * @param familyNames
 * @param nationalities
 * @param permanentNumbers
 * @param fullNames
 * @param driverIds
 * @param teams
 * @param circuit
 * @param country
 * @param circuitLength
 * @param raceDate
 * @param time
 * @param position
 * @param points
 * @param type
 * @return 0 by default, 1 if the sizes of the vectors of the driver are not the same
 */
int SaveToDB::saveToFile(std::vector<std::string> givenNames, std::vector<std::string> familyNames, std::vector<std::string> nationalities,
                         std::vector<std::string> permanentNumbers, std::vector<std::string> fullNames, std::vector<std::string> driverIds,
                         std::map<std::string, std::vector<std::string>> teams, std::vector<std::string> circuit, std::vector<std::string> country,
                         std::vector<std::string> circuitLength,  std::vector<std::string> raceDate, std::vector<std::string> time,
                         std::vector<std::string> position, std::vector<std::string> points, std::vector<std::string> driverAll,
                         std::vector<std::string> type, std::vector<std::string> fastestLapTimeAll, std::vector<std::string> fastestLapNrAll) {
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // get full path of executing application
    std::cout << "Getting path of executing application" << std::endl;
    char pBuf[256];
    size_t len = sizeof(pBuf);
#ifndef _WIN32
    int bytes = MIN(readlink("/proc/self/exe", pBuf, len), len - 1);
    if (bytes >= 0)
        pBuf[bytes] = '\0';
#else
    GetModuleFileName(NULL, pBuf, len);
#endif
    std::cout << "Path: " << pBuf << std::endl;
    std::string path = pBuf;
    path = path.substr(0, path.find("Week2Deel2"));


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // save to database
    GetCountries getCountries;
    std::ofstream fileSave("saveToDB.sql", std::ios::trunc);

    std::cout << "Saving all countries to database" << std::endl;
    getCountries.saveAllCountries(fileSave);

//    if (givenNames.size() != familyNames.size() || givenNames.size() != nationalities.size() ||
//        givenNames.size() != permanentNumbers.size() || givenNames.size() != fullNames.size() ||
//        givenNames.size() != driverIds.size()) {
//        std::cerr << "Error: the sizes of the vectors are not the same" <<std::endl;
//        if(givenNames.size() != familyNames.size())
//            std::cerr << "Size of givenNames: " << givenNames.size() << " size of familyNames: " << familyNames.size() << std::endl;
//        if(givenNames.size() != nationalities.size())
//            std::cerr << "Size of givenNames: " << givenNames.size() << " size of nationalities: " << nationalities.size() << std::endl;
//        if(givenNames.size() != permanentNumbers.size())
//            std::cerr << "Size of givenNames: " << givenNames.size() << " size of permanentNumbers: " << permanentNumbers.size() << std::endl;
//        if(givenNames.size() != fullNames.size())
//            std::cerr << "Size of givenNames: " << givenNames.size() << " size of fullNames: " << fullNames.size() << std::endl;
//        if(givenNames.size() != driverIds.size())
//            std::cerr << "Size of givenNames: " << givenNames.size() << " size of driverIds: " << driverIds.size() << std::endl;
//            return 1;
//    }
    //std::cout << "size of givenNames: " << givenNames.size() << "familyNames: " << familyNames.size() << "nationalities: " << nationalities.size() << "permanentNumbers: " << permanentNumbers.size() << "fullNames: " << fullNames.size() << "driverIds: " << driverIds.size() << std::endl;
    std::cout << "Saving coureur info" << std::endl;
    // fill sql statements for the table coureur while using the permanent numbers as the id this is only possible for any driver after 2015
    for (int i = 0; i < givenNames.size(); i++)
        fileSave << "INSERT IGNORE INTO coureur (coureurID, naam, foto) VALUES (" << permanentNumbers[i] << ", '" << fullNames[i] << "', LOAD_FILE('" << path << familyNames[i] << ".png'));" << std::endl;

    std::cout << "Saving team info" << std::endl;
    // fill sql statements for the table team
    for (int i = 0; i < teams.size(); i++)
        fileSave << "INSERT IGNORE INTO team (ID, naam) VALUES (" << i << ", '" << teams[driverIds[i]][0] << "');"
                 << std::endl;

    std::cout << "Saving circuit info" << std::endl;
    // fill sql statements for the table circuit
    for (int i = 0; i < circuit.size(); i++)
    {
        std::cout << "Country: " << country[i] << std::endl;
        std::cout << "Location: " << getCountries.countryConverter(country[i]) << std::endl;
        fileSave << "INSERT IGNORE INTO circuit (ID, circuitNaam, landID, lengte, foto) VALUES (" << i << ", '" << circuit[i] << "', " << getCountries.countryConverter(country[i]) << ", " << circuitLength[i] << ", LOAD_FILE('" << path << circuit[i] << ".png" << "'));" << std::endl;
    }

    std::cout << "Saving result info" << std::endl;
    // fill sql statements for the table result
    for(int i = 0; i < driverAll.size(); i++) // might be issues with saving etc
        fileSave << "INSERT INTO resultaat (resultaatID, score, position) VALUES (" << i << ", " << points[i] << ", " << position[i] << ");" << std::endl;

    std::cout << "Saving race info" << std::endl;
    // fill sql statements for the table race
    for(int i = 0; i < type.size(); i++)
        // id, circuitID, landID, resultID, type
//        fileSave << "INSERT INTO race (ID, circuitID, landID, resultID, type) VALUES (" << i << ", " << i << ", " << getCountries.countryConverter(country[i]) << ", " << i*20 << ", " << type[i] << ");" << std::endl;

    std::cout << "Saving kalender info" << std::endl;
    // fill sql statements for the table kalender
    for(int i = 0; i < raceDate.size(); i++)
        fileSave << "INSERT INTO kalender (ID, raceID, datum) VALUES (" << i << ", " << i << ", " << raceDate[i] << ");" << std::endl;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::cout << "Starting on intermediair tables" << std::endl;

    std::cout << "Saving landcoureur info" << std::endl;
    // fill sql statements for landcoureur table
    for(int i = 0; i < nationalities.size(); i++)
        fileSave << "INSERT IGNORE INTO landCoureur (ID, landID, coureurID) VALUES (" << i << ", "<< getCountries.countryConverter(nationalities[i]) << ", " << permanentNumbers[i] << ");" << std::endl;

    std::cout << "Saving teamcoureur info" << std::endl;
    // fill sql statements for teamcoureur table
    for(int i = 0; i < teams.size(); i++)
        fileSave << "INSERT IGNORE INTO teamCoureur (ID, teamID, coureurID) VALUES (" << i << ", '"<< teams[driverIds[i]][0] << "', " << permanentNumbers[i] << ");" << std::endl;

    for(int i = 0; i < driverAll.size(); i++)
        fileSave << "INSERT INTO coureurResultaat (ID, resultaatID, coureurID) VALUES (" << i << ", " << i << ", " << driverAll[i] << ");" << std::endl;

    // kalenderteam? Hoe willen we dat doen?!?

    fileSave.close();

    return 0;
}