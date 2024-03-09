//
// Created by flits on 3/3/24.
//

#ifndef WEEK2DEEL2_GETIMAGE_H
#define WEEK2DEEL2_GETIMAGE_H

#include <string>
#include <fstream>

class getImage {
public:
    getImage();
    virtual ~getImage();
    int getTheImage(std::string url, std::string name);
};


#endif //WEEK2DEEL2_GETIMAGE_H
