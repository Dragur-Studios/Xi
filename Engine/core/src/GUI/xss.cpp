#include "xss.h"

#include "styleSheet.h"

#include <regex>
#include <string>
#include <vector>


struct SelectorBlock
{
    std::string selector;
    StyleSheet styleSheet;
};


ImVec4 ExtractImVec4(const std::string& value)
{
    ImVec4 vec4Value;

    std::istringstream valueStream(value);

    valueStream >> vec4Value.x;
    valueStream.ignore(std::numeric_limits<std::streamsize>::max(), ','); // Ignore the comma and any whitespace after it
    valueStream >> vec4Value.y;
    valueStream.ignore(std::numeric_limits<std::streamsize>::max(), ','); // Ignore the comma and any whitespace after it
    valueStream >> vec4Value.z;
    valueStream.ignore(std::numeric_limits<std::streamsize>::max(), ','); // Ignore the comma and any whitespace after it
    valueStream >> vec4Value.w;

    return vec4Value;
}


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

void ParseStyleProperties(const std::string& styleProperties, StyleSheet& styleSheet)
{
    std::istringstream iss(styleProperties);
    std::string line;

    while (std::getline(iss, line))
    {
        std::string key;
        std::string value;
        // Split the line into key and value based on the ":" separator

        std::istringstream lineStream(line);
        std::getline(lineStream, key, ':');
        std::getline(lineStream, value);

        // Trim leading and trailing whitespaces from key and value
        key = TrimWhitespace(key);
        value = TrimWhitespace(value);

        // Trim leading and trailing whitespaces from key and value strings
        // (You can implement a helper function for trimming whitespaces)

        // Process the property and assign values to the corresponding fields in the styleSheet

        if (key == "width")
        {
            styleSheet.width = std::stof(value);
        }
        else if (key == "height")
        {
            styleSheet.height = std::stof(value);
        }
        else if (key == "rounding")
        {
            styleSheet.rounding = std::stof(value);
        }
        else if (key == "padding")
        {
            styleSheet.padding = ExtractImVec4(value.substr(0, value.size() - 1));
        }
        else if (key == "margin")
        {
            styleSheet.margin = ExtractImVec4(value.substr(0, value.size() - 1));
        }
        /// shadow 
        else if (key == "shadow")
        {
            styleSheet.shadow = ExtractImVec4(value.substr(0, value.size() - 1));
        }
        else if (key == "shadow-color") {
            styleSheet.shadow_color.normal = ImGui::ColorConvertFloat4ToU32(ExtractImVec4(value.substr(0, value.size() - 1)));
        }
        else if (key == "shadow-color @active") {
            styleSheet.shadow_color.active = ImGui::ColorConvertFloat4ToU32(ExtractImVec4(value.substr(0, value.size() - 1)));
        }
        else if (key == "shadow-color @hover") {
            styleSheet.shadow_color.hover = ImGui::ColorConvertFloat4ToU32(ExtractImVec4(value.substr(0, value.size() - 1)));
        }
        /// background 
        else if (key == "background-color") {
            styleSheet.background_color.normal = ImGui::ColorConvertFloat4ToU32(ExtractImVec4(value.substr(0, value.size() - 1)));
        }
        else if (key == "background-color @active") {
            styleSheet.background_color.active = ImGui::ColorConvertFloat4ToU32(ExtractImVec4(value.substr(0, value.size() - 1)));
        }
        else if (key == "background-color @hover") {
            styleSheet.background_color.hover = ImGui::ColorConvertFloat4ToU32(ExtractImVec4(value.substr(0, value.size() - 1)));
        }

        /// font 
        else if (key == "color") {
            styleSheet.font_color.normal = ImGui::ColorConvertFloat4ToU32(ExtractImVec4(value.substr(0, value.size()-1)));
        }
        else if (key == "color @active") {
            styleSheet.font_color.active = ImGui::ColorConvertFloat4ToU32(ExtractImVec4(value.substr(0, value.size() - 1)));
        }
        else if (key == "color @hover") {
            styleSheet.font_color.hover = ImGui::ColorConvertFloat4ToU32(ExtractImVec4(value.substr(0, value.size() - 1)));
        }
        /// border 
        else if (key == "border") {
            styleSheet.border = ExtractImVec4(value.substr(0, value.size() - 1));
        }
        else if (key == "border-color") {
            styleSheet.border_color.normal = ImGui::ColorConvertFloat4ToU32(ExtractImVec4(value.substr(0, value.size() - 1)));
        }
        else if (key == "border-color @active") {
            styleSheet.border_color.active = ImGui::ColorConvertFloat4ToU32(ExtractImVec4(value.substr(0, value.size() - 1)));
        }
        else if (key == "border-color @hover") {
            styleSheet.border_color.hover = ImGui::ColorConvertFloat4ToU32(ExtractImVec4(value.substr(0, value.size() - 1)));
        }

    }
}


void ParseSelectorBlocks(const std::string& xss, std::map<std::string, StyleSheet*>& styleMap)
{
    std::istringstream iss(xss);
    std::string line;
    std::string currentSelector;

    while (std::getline(iss, line))
    {
        if (!line.empty())
        {
            if (line.back() == '{')
            {
                // Start of a selector block
                currentSelector = line.substr(0, line.size() - 2);
            }
            else if (line.front() == '}')
            {
                // End of a selector block
                currentSelector.clear();
            }
            else if (!currentSelector.empty())
            {
                std::size_t colonPos = line.find(':');
                if (colonPos != std::string::npos)
                {
                    std::string property = line.substr(0, colonPos);
                    std::string value = line.substr(colonPos + 1);
                    value.pop_back(); // Remove ;

                    LOG_INFO("Processing: selector:" + currentSelector + " value: " + value);

                    // Check if the styleMap already contains the current selector
                    if (styleMap.find(currentSelector) == styleMap.end())
                    {
                        LOG_INFO("Creating " + currentSelector);
                        styleMap[currentSelector] = new StyleSheet();
                    }

                    // Parse the property-value pair using the updated ParseStyleProperties function
                    ParseStyleProperties(property + ":" + value, *styleMap[currentSelector]);
                }
            }
        }
    }
}
