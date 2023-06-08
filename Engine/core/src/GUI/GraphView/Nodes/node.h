#pragma once

#include "pch.h"
#include "defs.h"


enum class PinType {
    Input,
    Output
};

struct Pin {
    int id;
    PinType type;
};

struct Node {
    Node(const std::string& title, float x, float y, unsigned int title_color=0xFF244816);
    virtual ~Node();

    void Draw();
    virtual void Create() = 0;

    std::vector<Pin> pins;

    int id;
    struct {
        float x;
        float y;
    }position;


protected:
    void DrawTitleBox();
    void DrawPins();

    void AddPin(PinType type);


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



