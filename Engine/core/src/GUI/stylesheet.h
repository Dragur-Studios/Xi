#pragma once

#include "pch.h"
#include "defs.h"

#include "dependencies/imdom.h"




class iStyleProperty
{   
};

template<typename T>
class SingleValueProperty : public iStyleProperty {
public:
    SingleValueProperty(T defaultValue) : value{ defaultValue } {};
    T value;
};

template<typename T, int COUNT>
class MultiValueProperty  : public iStyleProperty {
public:
    MultiValueProperty(T defaultValue) {
        value.resize(COUNT);
        for (size_t i = 0; i < value.size(); i++)
        {
            value[i] = defaultValue;
        }
    };
    std::vector<T> value;
};

class PropertyFactory {
public:
    template<typename T>
    static iStyleProperty* SingleValue() {
        try {
            const std::type_info& type = typeid(T());
            
            LOG_INFO("Attempting to deduce type for value: " + type.name() + " | " + typeid(float).name())

            if (std::string(type.name()).contains(typeid(float).name())) {
                return new SingleValueProperty<float>(-1);
            }
            else if (std::string(type.name()).contains(typeid(ImTextAlignment).name())) {
                return new SingleValueProperty<ImTextAlignment>(ImTextAlignment::None);
            }
            else if (std::string(type.name()).contains(typeid(ImColorState).name())) {
                return new SingleValueProperty<ImColorState>(ImColorState::Default());
            }
            else if (std::string(type.name()).contains(typeid(ImFlexDirection).name())) {
                return new SingleValueProperty<ImFlexDirection>(ImFlexDirection::None);
            }

            // TYPE COULD NOT BE REDUCED
            LOG_WARNING("Type("+type.name()+ ") could not be deduced for default initilization!");
            return nullptr;
        }
        catch (const std::exception& ex) {
            LOG_ERROR("Memory could not be allocated for a SVP " + ex.what());
            return nullptr;
        }    
    };

    template<typename T, int COUNT>
    static iStyleProperty* MultiValue() {
        try {
            const std::type_info& type = typeid(T());
    

            if (std::string(type.name()).contains(typeid(float).name())) {
                return new MultiValueProperty<float, COUNT>(-1.0f);
            }
            else if (std::string(type.name()).contains(typeid(int).name())) {
                return new MultiValueProperty<int, COUNT>(-1);
            }

            // TYPE COULD NOT BE REDUCED
            LOG_WARNING("Type(" + type.name() + ") could not be deduced for default initilization!");
            return nullptr;
        }
        catch (const std::exception& ex) {
            LOG_ERROR("Memory could not be allocated for a MVP" + ex.what());
            return nullptr;
        }

    }

    static void Destroy(iStyleProperty* address) {
        
        try {
            delete ((void*)address);
        }
        catch (const std::exception& ex) {
            LOG_ERROR("Memory could not be freed for a SVP " + ex.what());
        }
    }
};


class StyleSheet
{
public:
    StyleSheet(){};
    ~StyleSheet() {};

    std::map<std::string, iStyleProperty*> properties ={
        {"width", PropertyFactory::SingleValue<float>()},
        {"height", PropertyFactory::SingleValue<float>()},
        {"rounding", PropertyFactory::SingleValue<float>()},
        {"padding", PropertyFactory::MultiValue<float, 4>()},
        {"margin", PropertyFactory::MultiValue<float, 4>()},
        {"shadow", PropertyFactory::MultiValue<float, 4>()},
        {"border", PropertyFactory::MultiValue<float, 4>()},
        {"shadow-color", PropertyFactory::SingleValue<ImColorState>()},
        {"text-align", PropertyFactory::SingleValue<ImTextAlignment>()},
        {"color", PropertyFactory::SingleValue<ImColorState>()},
        {"background-color", PropertyFactory::SingleValue<ImColorState>()},
        {"font-color", PropertyFactory::SingleValue<ImColorState>()},
        {"border-color", PropertyFactory::SingleValue<ImColorState>()},
        {"flex-direction", PropertyFactory::SingleValue<ImFlexDirection>()}
    };

};
