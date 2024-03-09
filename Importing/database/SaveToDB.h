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
                   std::map<std::string, std::vector<std::string>> teams);
};


#endif //WEEK2DEEL2_SAVETODB_H
