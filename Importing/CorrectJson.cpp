//
// Created by flits on 3/4/24.
//

#include "CorrectJson.h"
#include <sstream>
#include <iomanip>

CorrectJson::CorrectJson() {

}

CorrectJson::~CorrectJson() {

}

std::string CorrectJson::correctJson(const std::string &input) {
    std::istringstream stream(input);
    std::ostringstream beautified;

    int indentLevel = 0;
    char ch;

    while (stream.get(ch)) {
        switch (ch) {
            case '{':
            case '[':
                beautified << ch << "\n" << std::setw(++indentLevel * 2) << "";
                break;
            case '}':
            case ']':
                beautified << "\n" << std::setw(--indentLevel * 2) << "" << ch;
                break;
            case ',':
                beautified << ch << "\n" << std::setw(indentLevel * 2) << "";
                break;
            case ':':
                beautified << ": ";
                break;
            default:
                beautified << ch;
        }
    }

    return beautified.str();
}