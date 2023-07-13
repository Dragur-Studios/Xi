#include "xss.h"

#include "styleSheet.h"
#include <IO/FileSystem.h>

#include "Visual Elements/visual_element.h"

#include "IO/file_helpers.h"

float lerp(float v0, float v1, float t) {
    return (1 - t) * v0 + t * v1;
}

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

    valueStream.clear();

    return vec4Value;
}

std::map<std::string, class StyleSheet*> XssEngine::styleMap{};

std::string ConvertRGBAToABGR(const std::string& hex)
{
    // Check if the string has the correct format (0xRGBA)
    if (hex.size() == 10 && hex.substr(0, 2) == "0x")
    {
        // Extract the R, G, B, A components
        // abgr 0x RR GG BB AA
        //      01 23 45 67 89

        auto buffer = hex.data();

        std::string r = "";
        r += buffer[2];
        r +=  buffer[3];

        std::string g = "";
        g += buffer[4];
        g += buffer[5];

        std::string b ="";
        b += buffer[6];
        b += buffer[7];

        std::string a = "";
        a += buffer[8];
        a += buffer[9];

        // Create the ABGR string (0xABGR)
        std::string abgrString = "0x" + a + b + g + r;
        LOG_INFO("agbr string = " + abgrString);
        return abgrString;
    }
    else
    {
        LOG_ERROR("INVALID FORMAT!");
        // Invalid format, return the original string
        return hex;
    }
}


ImU32 ParseColorValue(const std::string& rgba)
{
    auto agbr = ConvertRGBAToABGR(rgba);
    // Check if the value is in the format of a hexadecimal color code (0xFFFFFFFF)
    if (agbr.size() == 10 && agbr[0] == '0' && agbr[1] == 'x')
    {
        // Extract the hexadecimal value and convert it to unsigned integer
        std::string hexCode = agbr.substr(2);
        return std::stoul(hexCode, nullptr, 16);
    }
    else
    {
        // Assume the value is in the format of a vec4 color (R, G, B, A)
        ImVec4 color = ExtractImVec4(rgba);
        return ImGui::ColorConvertFloat4ToU32(color);
    }
}

void XssEngine::ParseStyleProperty(const std::string& property, const std::string& value, StyleSheet& styleSheet)
{
    auto key = TrimWhitespace(property);
    auto val = TrimWhitespace(value);

    if (key == "width")
    {
        //if (val.contains("%")) {
        //    auto numStr = val;
        //    numStr.pop_back(); // remove %
        //    
        //    float num = std::atof(numStr.c_str());
        //    
        //    if (num > 100.0f) num == 100.0f;
        //    if (num < 0.0f) num == 0.0f;

        //    float t = num / 100.0f;
        //    
        //    auto prop = static_cast<SingleValueProperty<float>*>(styleSheet.properties["width"]);
        //    prop->value = lerp(0.0f, windowSize.x, t);

        //}
        //else {
            auto prop = static_cast<SingleValueProperty<float>*>(styleSheet.properties["width"]);
            prop->value = std::stof(val);
        //}
    }
    else if (key == "height")
    {
        //if (val.contains("%")) {
        //    auto numStr = val;
        //    numStr.pop_back(); // remove %

        //    float num = std::atof(numStr.c_str());

        //    if (num > 100.0f) num == 100.0f;
        //    if (num < 0.0f) num == 0.0f;

        //    float t = num / 100.0f;

        //    auto prop = static_cast<SingleValueProperty<float>*>(styleSheet.properties["height"]);
        //    prop->value = lerp(0.0f, windowSize.y, t);
        //}
        //else {
            auto prop = static_cast<SingleValueProperty<float>*>(styleSheet.properties["height"]);
            prop->value = std::stof(val);
        //}
    }
    else if (key == "rounding")
    {
        auto prop = static_cast<SingleValueProperty<float>*>(styleSheet.properties["rounding"]);
        prop->value = std::stof(val);
    }
    else if (key == "padding")
    {
        auto prop = static_cast<MultiValueProperty<float, 4>*>(styleSheet.properties["padding"]);
        auto v4 = ExtractImVec4(val.substr(0, val.size() - 1));
        prop->value[0] = v4.x;
        prop->value[1] = v4.y;
        prop->value[2] = v4.z;
        prop->value[3] = v4.w;
    }
    else if (key == "margin")
    {
        auto prop = static_cast<MultiValueProperty<float, 4>*>(styleSheet.properties["margin"]);
        auto v4 = ExtractImVec4(val.substr(0, val.size() - 1));
        prop->value[0] = v4.x;
        prop->value[1] = v4.y;
        prop->value[2] = v4.z;
        prop->value[3] = v4.w;
    }
    else if (key == "text-align") {
        auto prop = static_cast<SingleValueProperty<ImTextAlignment>*>(styleSheet.properties["text-align"]);
        
        if (value == "center") {
            prop->value = ImTextAlignment::Center;
        }
        else if (value == "center-left") {
            prop->value = ImTextAlignment::Center;
        }
        else if (value == "top-left") {
            prop->value = ImTextAlignment::Center;
        }
        else if (value == "bottom-left") {
            prop->value = ImTextAlignment::Center;
        }
        else if (value == "center-right") {
            prop->value = ImTextAlignment::Center;
        }
        else if (value == "top-right") {
            prop->value = ImTextAlignment::Center;
        }
        else if (value == "bottom-right") {
            prop->value = ImTextAlignment::Center;
        }
    }
    else if (key == "flex-direction") {
        auto prop = static_cast<SingleValueProperty<ImFlexDirection>*>(styleSheet.properties["flex-direction"]);

        if (value == "row") {
            prop->value = ImFlexDirection::Row;
        }
        else if (value == "column") {
            prop->value = ImFlexDirection::Column;
        }
        else {
            LOG_ERROR("Flex-Direction Value not Recognized.");
        }
    }

    /// shadow 
    else if (key == "shadow")
    {
        auto prop = static_cast<MultiValueProperty<float, 4>*>(styleSheet.properties["shadow"]);
        auto v4 = ExtractImVec4(val.substr(0, val.size() - 1));
        prop->value[0] = v4.x;
        prop->value[1] = v4.y;
        prop->value[2] = v4.z;
        prop->value[3] = v4.w;
    }
    else if (key == "shadow-color") {
     
        auto prop = static_cast<SingleValueProperty<ImColorState>*>(styleSheet.properties["shadow-color"]);
        auto& colorState = prop->value;
        
        colorState.normal = ParseColorValue(val);
    }
    else if (key == "shadow-color @active") {
        auto prop = static_cast<SingleValueProperty<ImColorState>*>(styleSheet.properties["shadow-color"]);
        auto& colorState = prop->value;

        colorState.active = ParseColorValue(val);
    }
    else if (key == "shadow-color @hover") {
        auto prop = static_cast<SingleValueProperty<ImColorState>*>(styleSheet.properties["shadow-color"]);
        auto& colorState = prop->value;

        colorState.hover= ParseColorValue(val);
    }
    /// background 
    else if (key == "background-color") {
        auto prop = static_cast<SingleValueProperty<ImColorState>*>(styleSheet.properties["background-color"]);
        auto& colorState = prop->value;

        colorState.normal = ParseColorValue(val);
    }
    else if (key == "background-color @active") {
        auto prop = static_cast<SingleValueProperty<ImColorState>*>(styleSheet.properties["background-color"]);
        auto& colorState = prop->value;

        colorState.active = ParseColorValue(val);
    }
    else if (key == "background-color @hover") {
        auto prop = static_cast<SingleValueProperty<ImColorState>*>(styleSheet.properties["background-color"]);
        auto& colorState = prop->value;

        colorState.hover = ParseColorValue(val);
    }

    /// font 
    else if (key == "color") {
        auto prop = static_cast<SingleValueProperty<ImColorState>*>(styleSheet.properties["color"]);
        auto& colorState = prop->value;

        colorState.normal = ParseColorValue(val);
    }
    else if (key == "color @active") {
        auto prop = static_cast<SingleValueProperty<ImColorState>*>(styleSheet.properties["color"]);
        auto& colorState = prop->value;

        colorState.active = ParseColorValue(val);
    }
    else if (key == "color @hover") {
        auto prop = static_cast<SingleValueProperty<ImColorState>*>(styleSheet.properties["color"]);
        auto& colorState = prop->value;

        colorState.hover = ParseColorValue(val);
    }
    /// border 
    else if (key == "border") {
        auto prop = static_cast<MultiValueProperty<float, 4>*>(styleSheet.properties["border"]);
        auto v4 = ExtractImVec4(val.substr(0, val.size() - 1));
        prop->value[0] = v4.x;
        prop->value[1] = v4.y;
        prop->value[2] = v4.z;
        prop->value[3] = v4.w;
    }
    else if (key == "border-color") {
        auto prop = static_cast<SingleValueProperty<ImColorState>*>(styleSheet.properties["border-color"]);
        auto& colorState = prop->value;

        colorState.normal = ParseColorValue(val);
    }
    else if (key == "border-color @active") {
	    auto prop = static_cast<SingleValueProperty<ImColorState>*>(styleSheet.properties["border-color"]);
	    auto& colorState = prop->value;

	    colorState.active = ParseColorValue(val);
	}
    else if (key == "border-color @hover") {
        auto prop = static_cast<SingleValueProperty<ImColorState>*>(styleSheet.properties["border-color"]);
        auto& colorState = prop->value;

        colorState.hover= ParseColorValue(val);
    }
    
    /// ERROR
    else {
        LOG_ERROR("compilation failed: slector not recognized: " + key);
    }
    
}

void XssEngine::Compile(const std::string& filepath)
{
    std::string xss_buffer;

    FileSystem::File::Read(filepath, xss_buffer);

    XssEngine::Parse(xss_buffer);
}

StyleSheet* XssEngine::GetClass(const std::string& className)
{
    return styleMap[className];
}

StyleSheet* XssEngine::GetID(const std::string& id) {
    return styleMap["#" + id];
}

StyleSheet* XssEngine::GetName(const std::string& name)
{
    return styleMap["." + name];
}

void XssEngine::UpdateNameVars(const std::string& selector, StyleSheet& sheet)
{
    // Get the named selector properties
    auto namedProperties = GetName(selector);
    
    // Ensure the named selector exists and has properties
    if (namedProperties != nullptr && !namedProperties->properties.empty())
    {
        // Iterate over each property in the named selector
        for (const auto& namedProperty : namedProperties->properties)
        {
            const std::string& propertyName = namedProperty.first;
            auto propertyValue = namedProperty.second;
            
            // Find the corresponding property in the stylesheet
            // first attempt to see if its a single value property 
            
            if (static_cast<SingleValueProperty<float>*>(propertyValue) != nullptr) {
                auto val = static_cast<SingleValueProperty<float>*>(propertyValue)->value;
                if (val == -1)
                    continue;
            }
            else if(static_cast<SingleValueProperty<ImTextAlignment>*>(propertyValue) != nullptr) {
                auto val = static_cast<SingleValueProperty<ImTextAlignment>*>(propertyValue)->value;
                if (val == ImTextAlignment::None)
                    continue;
            }
            else if (static_cast<SingleValueProperty<ImFlexDirection>*>(propertyValue) != nullptr) {
                auto val = static_cast<SingleValueProperty<ImFlexDirection>*>(propertyValue)->value;
                if (val == ImFlexDirection::None)
                    continue;
            }
            else if (static_cast<MultiValueProperty<float, 4>*>(propertyValue) != nullptr) {
                auto prop = static_cast<MultiValueProperty<float, 4>*>(propertyValue);
                if (prop->value[0] == -1 || prop->value[1] == -1) {
                    continue;
                }
            }
            auto it = sheet.properties.find(propertyName);
            
            // Update the property value in the stylesheet if it exists and is different
            if (it != sheet.properties.end() && it->second != propertyValue)
            {
                it->second = propertyValue;
            }
        }
    }
}


void XssEngine::UpdateIDVars(const std::string& selector, StyleSheet& sheet)
{
    auto temp = GetID(selector);
    // for each property in the new value
    for (auto prop : temp->properties)
    {
        // find the corrisponding property in the stylesheet we are updating
        auto it = sheet.properties.find(prop.first);
        // as long as its found
        if (it != sheet.properties.end()) {
            // ensure that its not already the same value as prior
            if (prop.second != it->second) {
                // assign the value found to the stylesheet
                it->second = prop.second;
            }
        }
    }

}

StyleSheet* XssEngine::GetStyleSheet(VisualElement* element)
{
    auto stylesheet = XssEngine::GetClass(element->_class);
    
    if (stylesheet == nullptr)
        return nullptr;

    // name is more likely.
    if (!element->_name.empty()) {
        // replace any previously set styles.
        UpdateNameVars(element->_name, *stylesheet);
    }
    // an ID will override name
    if (!element->_id.empty()) {
        // replace any previously set  styles 
        UpdateIDVars(element->_id, *stylesheet);
    }

    return stylesheet;
}



void XssEngine::Parse(const std::string& xss)
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
                LOG_INFO("Parsing selector:\t" + currentSelector);
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


                    // Check if the styleMap already contains the current selector
                    if (styleMap.find(currentSelector) == styleMap.end())
                    {
                        LOG_INFO("Creating " + currentSelector);
                        styleMap.emplace(currentSelector, new StyleSheet());
                    }

                    LOG_INFO("Found Property::\t " + property + "  value: " + value);
                    // Parse the property-value pair using the updated ParseStyleProperties function
                    
                    auto sheet = styleMap.at(currentSelector);
                    ParseStyleProperty(property, value, *sheet);
                }
            }
        }
    }
}




