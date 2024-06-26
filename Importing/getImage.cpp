//
// Created by flits on 3/3/24.
//

#include "getImage.h"
#include <iostream>
#include <curl/curl.h>
#include <string>

getImage::getImage() {

}

getImage::~getImage() {

}

std::string pathToWebPage = "/home/flits/CLionProjects/DAB2/webpage/img/";

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::ofstream* imageFile) {
    size_t totalSize = size * nmemb;
    imageFile->write((char*)contents, totalSize);
    return totalSize;
}

int getImage::getTheImage(std::string url, std::string nameIn) {
    // Initialize cURL
    CURL* curl = curl_easy_init();
    std::string name = (pathToWebPage + nameIn + ".png");

    if (curl) {
        // Open a file to write the image
        std::ofstream imageFile(name, std::ios::binary);

        // Set the URL to download
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the callback function to write data to the file
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &imageFile);

        // Perform the HTTP request and download the image
        CURLcode res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "cURL failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Clean up
        curl_easy_cleanup(curl);

        // Close the file
        imageFile.close();
    }

    return 0;
}