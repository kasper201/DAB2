//
// Created by flits on 3/10/24.
//

#ifndef WEEK2DEEL2_GETCOUNTRIES_H
#define WEEK2DEEL2_GETCOUNTRIES_H

#include <string>

class GetCountries {
public:
    GetCountries();
    virtual ~GetCountries();
    static int countryConverter(const std::string &country);
    static void saveAllCountries(std::ofstream &file);
};


#endif //WEEK2DEEL2_GETCOUNTRIES_H
