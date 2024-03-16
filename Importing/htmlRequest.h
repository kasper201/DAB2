//
// Created by flits on 3/4/24.
//

#ifndef WEEK2DEEL2_HTMLREQUEST_H
#define WEEK2DEEL2_HTMLREQUEST_H
#include <string>

class htmlRequest {
public:
    htmlRequest();
    virtual ~htmlRequest();
    std::string getRequest(const std::string &url);
};


#endif //WEEK2DEEL2_HTMLREQUEST_H
