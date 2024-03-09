//
// Created by flits on 3/9/24.
//

#include "SaveToDB.h"

#include <iostream>
#include <fstream>
#include <unistd.h>

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
 * @return 0 by default, 1 if the sizes of the vectors are not the same
 */
int SaveToDB::saveToFile(std::vector<std::string> givenNames, std::vector<std::string> familyNames, std::vector<std::string> nationalities,
                         std::vector<std::string> permanentNumbers, std::vector<std::string> fullNames, std::vector<std::string> driverIds,
                         std::map<std::string, std::vector<std::string>> teams)
{
    // get full path of executing application
    char pBuf[256];
    size_t len = sizeof(pBuf);
    int bytes = MIN(readlink("/proc/self/exe", pBuf, len), len - 1);
    if(bytes >= 0)
        pBuf[bytes] = '\0';
    std::cout << "Path: " << pBuf << std::endl;
    std::string path = pBuf;
    path = path.substr(0, path.find("Week2Deel2"));

    std::ofstream fileSave("saveToDB.sql", std::ios::trunc);
    if(givenNames.size() != familyNames.size() || givenNames.size() != nationalities.size() || givenNames.size() != permanentNumbers.size() || givenNames.size() != fullNames.size() || givenNames.size() != driverIds.size()) {
        std::cerr << "Error: the sizes of the vectors are not the same" << std::endl;
        return 1;
    }
    //std::cout << "size of givenNames: " << givenNames.size() << "familyNames: " << familyNames.size() << "nationalities: " << nationalities.size() << "permanentNumbers: " << permanentNumbers.size() << "fullNames: " << fullNames.size() << "driverIds: " << driverIds.size() << std::endl;
    std::cout << "Saving coureur info" << std::endl;
    // fill sql statements for the table coureur while using the permanent numbers as the id
    for(int i = 0; i < givenNames.size(); i++)
        fileSave << "INSERT INGORE INTO coureur (id, Naam, selfie) VALUES (" << permanentNumbers[i] << ", " << fullNames[i] << ", LOAD_FILE('" << path << familyNames[i] << ".png'));" << std::endl;

    std::cout << "Saving land info" << std::endl;
    // fill sql statements for the table land
    for(int i = 0; i < nationalities.size(); i++)
        fileSave << "INSERT INGORE INTO land (id, naam) VALUES (" << i << ", " << nationalities[i] << ");" << std::endl;

    std::cout << "Saving team info" << std::endl;
    // fill sql statements for the table team
    for(int i = 0; i < teams.size(); i++)
        fileSave << "INSERT INGORE INTO team (id, naam) VALUES (" << i << ", " << teams[driverIds[i]][0] << ");" << std::endl;


    std::cout << "Starting on intermediair tables" << std::endl;
    return 0;
}