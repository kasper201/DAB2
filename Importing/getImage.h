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
    void setPath(std::string pathIn);
    int getTheImage(const std::string& url, const std::string& name);
private:
    std::string path = "/home/flits/CLionProjects/DAB2/webpage/img/";
};


#endif //WEEK2DEEL2_GETIMAGE_H
