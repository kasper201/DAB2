//
// Created by flits on 3/3/24.
//

#ifndef WEEK2DEEL2_CIRCUITINFO_H
#define WEEK2DEEL2_CIRCUITINFO_H
#include "CorrectJson.h"
#include "htmlRequest.h"

#include <string>

class CircuitInfo {
public:
    CircuitInfo();
    ~CircuitInfo();
    int circuit(int year);
    std::string findInHtml(std::string html);
    std::string findCircuitLength(int circuitNr, int year);
    int circuitImage(std::string circuitC); // corrected circuit
private:
    std::string getF1CircuitName(int circuitNr, int year);
private:
    htmlRequest request;
    CorrectJson correctJson;
};


#endif //WEEK2DEEL2_CIRCUITINFO_H
