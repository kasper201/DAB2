//
// Created by flits on 3/10/24.
//

#include "GetCountries.h"
#include "CorrectJson.h"
#include "htmlRequest.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

struct Record {
    std::string country;
    std::string adjectival;
};

std::vector<Record> readCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Record> data;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string country, adjectival;
        std::getline(iss, country, ',');
        std::getline(iss, adjectival, ',');

        data.push_back({country, adjectival});
    }

    return data;
}

GetCountries::GetCountries() {

}

GetCountries::~GetCountries() {

}

int binarySearch(const std::vector<Record>& data, const std::string& key) {
    int low = 0;
    int high = data.size() - 1;

    while (low <= high) {
        if(data[low].country == key || data[low].adjectival == key) {
            return low;
        }
        low++;
    }

    return -1; // Return -1 if not found
}

int GetCountries::countryConverter(const std::string &country) {
    std::vector<Record> data = readCSV("listcountries.csv");

    return binarySearch(data, country);
}

/**
 * @brief Save all countries to a file
 */
void GetCountries::saveAllCountries(std::ofstream &file) {

    std::vector<Record> data = readCSV("listcountries.csv");

    for(int i = 0; i < data.size(); i++) {
        file << "INSERT INTO land (landID, naam, adjectival) VALUES (" << i << ", " << std::quoted(data[i].country) << ", " << std::quoted(data[i].adjectival) << ");" << std::endl;
        std::cout << "country: " << data[i].country << " adjectival: " << data[i].adjectival << std::endl;
    }

}
