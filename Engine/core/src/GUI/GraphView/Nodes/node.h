#pragma once

#include "pch.h"
#include "defs.h"

#include <functional>

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
    None=0,
    NoEdit,
};

struct Pin {
    int id;
    PinType type;
    PinFlags flags;
    PinClass classification;

    float* data;

};

using NodeOperation = void(*)();

struct Node {

    Node(const std::string& title, float x, float y, unsigned int title_color=0xFF244816);
    virtual ~Node();

    void Update();
    void Draw();

    virtual void OnLink(Pin outputPin, Pin inputPin) = 0;
    virtual void OnCreateGUI() = 0;

    std::vector<Pin> pins;

    int id;
    struct {
        float x;
        float y;
    }position;


protected:
    void DrawTitleBox();
    void DrawPins();

    void AddPin(PinType type, PinClass classification, PinFlags flags=PinFlags::None);

    std::function<void()> operation;
    
private:


    std::string title;

    unsigned int title_bar_color;
    unsigned int title_bar_color_hvr;

    
    

// STATIC HELPERS 
protected:

    static int CreateNodeID() { return node_id++; }
    static int CreateAttributeID() { return attr_id++; }

private:
    static int node_id; // max nodes = 2,147,483,647
    static int attr_id; // max attributes = 2,147,483,647
};



