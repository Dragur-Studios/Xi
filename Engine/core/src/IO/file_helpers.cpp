#include "file_helpers.h"

#include <sstream>

std::string TrimWhitespace(const std::string& str)
{
    // Find the first non-whitespace character
    std::size_t start = str.find_first_not_of(" \t");

    if (start == std::string::npos)
    {
        // If the string is all whitespace, return an empty string
        return "";
    }

    // Find the last non-whitespace character
    std::size_t end = str.find_last_not_of(" \t");

    // Extract the substring between the first and last non-whitespace characters
    return str.substr(start, end - start + 1);
}

bool ParseLine(const std::string& line, std::string& variable, std::string& value)
{
    std::istringstream iss(line);
    
    if (std::getline(iss, variable, '=') && std::getline(iss, value, ';')) {
        TrimWhitespace(variable);
        TrimWhitespace(value);
        return true;
    }

    return false;
}
