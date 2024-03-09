cmake_minimum_required(VERSION 3.26)
project(Week2Deel2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Week2Deel2 main.cpp
        "Driver info/driverinfo.cpp"
        "Driver info/driverinfo.h"
        Circuit/CircuitInfo.cpp
        Circuit/CircuitInfo.h
        getImage.cpp
        getImage.h
        results/Results.cpp
        results/Results.h
        htmlRequest.cpp
        htmlRequest.h
        CorrectJson.cpp
        CorrectJson.h
        database/SaveToDB.cpp
        database/SaveToDB.h)

find_package(CURL REQUIRED)

target_include_directories(Week2Deel2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CURL_INCLUDE_DIR})
target_link_libraries(Week2Deel2 PRIVATE ${CURL_LIBRARY})