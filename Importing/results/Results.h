//
// Created by flits on 3/4/24.
//

#ifndef WEEK2DEEL2_RESULTS_H
#define WEEK2DEEL2_RESULTS_H
#include "htmlRequest.h"
#include "CorrectJson.h"

#include <vector>

class Results {
public:
    Results();
    virtual ~Results();
    int results(int year, int race, std::vector<std::string> &dateAll, std::vector<std::string> &timeAll, std::vector<std::string> &driverAll, std::vector<std::string> &positionAll, std::vector<std::string> &pointsAll, std::vector<std::string> &type);
private:
    int getSprintResults(int year, int race);
private:
    htmlRequest request;
    CorrectJson correctJson;
    std::vector<std::string> date, time, driver, position, points, type;
};


#endif //WEEK2DEEL2_RESULTS_H
