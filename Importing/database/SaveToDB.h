//
// Created by flits on 3/9/24.
//

#ifndef WEEK2DEEL2_SAVETODB_H
#define WEEK2DEEL2_SAVETODB_H

#include <string>
#include <vector>
#include <map>

class SaveToDB {
public:
    SaveToDB();
    ~SaveToDB();
    int saveToFile(std::vector<std::string> givenNames,std::vector<std::string> familyNames,std::vector<std::string> nationalities,
                   std::vector<std::string> permanentNumbers,std::vector<std::string> fullNames,std::vector<std::string> driverIds,
                   std::map<std::string, std::vector<std::string>> teams, std::vector<std::string> circuit, std::vector<std::string> country,
                   std::vector<std::string> circuitLength, std::vector<std::string> raceDate, std::vector<std::string> time,
                   std::vector<std::string> position, std::vector<std::string> points, std::vector<std::string> driverAll,
                   std::vector<std::string> type, std::vector<std::string> fastestLapTimeAll, std::vector<std::string> fastestLapNrAll,
                   std::vector<std::string> locationLAT, std::vector<std::string> circuitLAT, std::string homePath);

private:
};


#endif //WEEK2DEEL2_SAVETODB_H
