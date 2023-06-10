#pragma once


enum class PinType {
    Input,
    Output
};

enum class PinClass {
    Float,
    Float2,
    Float3,
    Float4,
};

enum class PinFlags {
    None = 0,
    NoEdit,
};


struct Pin {
    int id;
    
    PinType type;
    PinFlags flags;
    PinClass classification;

    void* data;


};

