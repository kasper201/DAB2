//
// Created by flits on 3/4/24.
//

#include "htmlRequest.h"

#include <iostream>
#include <curl/curl.h>

htmlRequest::htmlRequest() {

}

htmlRequest::~htmlRequest() {

}

size_t WriteCallbackCircuit(void* contents, size_t size, size_t nmemb, std::string* output) // function to write the response from the API
{
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

std::string htmlRequest::getRequest(const std::string &url) {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    std::string response;

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallbackCircuit);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return response;
}