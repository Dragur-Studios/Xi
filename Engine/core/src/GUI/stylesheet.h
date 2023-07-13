#pragma once

#include "pch.h"
#include "defs.h"

#include "dependencies/imdom.h"


enum TextAlignment {
    Top_Left,
    Top_Middle,
    Top_Right,
    Center_Right,
    Bottom_Right,
    Bottom_Middle,
    Bottom_Left,
    Center_Left,
    Center
};

enum FlexDirection {
    Row,
    Column
};

class iStyleProperty
{   
};

template<typename T>
class SingleValueProperty : public iStyleProperty {
public:
    T value;
};

template<typename T, int COUNT>
class MultiValueProperty  : public iStyleProperty {
public:
    T value[COUNT];
};

class PropertyFactory {
public:
    template<typename T>
    static iStyleProperty* SingleValue() {
        try {

            auto address = new SingleValueProperty<T>();
            return (iStyleProperty*)address;
        }
        catch (const std::exception& ex) {
            LOG_ERROR("Memory could not be allocated for a SVP");
            return nullptr;
        }    
    };

    template<typename T, int COUNT>
    static iStyleProperty* MultiValue() {
        try {

            auto address = new MultiValueProperty<T, COUNT>();
            return (iStyleProperty*)address;
        }
        catch (const std::exception& ex) {
            LOG_ERROR("Memory could not be allocated for a SVP");
            return nullptr;
        }

    }

    static void Destroy(iStyleProperty* address) {
        
        try {
            delete ((void*)address);
        }
        catch (const std::exception& ex) {
            LOG_ERROR("Memory could not be freed for a SVP");
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
        {"text-align", PropertyFactory::SingleValue<TextAlignment>()},
        {"color", PropertyFactory::SingleValue<ImColorState>()},
        {"background-color", PropertyFactory::SingleValue<ImColorState>()},
        {"border-color", PropertyFactory::SingleValue<ImColorState>()},
        {"flex-direction", PropertyFactory::SingleValue<FlexDirection>()}
    };

};
