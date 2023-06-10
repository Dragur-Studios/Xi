#pragma once

#include "pch.h"
#include "defs.h"

#include <functional>

struct Node {

    Node(const std::string& title, float x, float y, unsigned int title_color=0xFF244816);
    virtual ~Node();

    void Update();
    void Draw();

    virtual void OnLink(struct Pin outputPin, struct  Pin inputPin) = 0;
    virtual void OnCreateGUI() = 0;

    std::vector<struct Pin> pins;

    int id;
    struct {
        float x;
        float y;
    }position;


protected:
    void DrawTitleBox();
    void DrawPins();

    void AddPin(enum class PinType type, enum class PinClass classification, enum class PinFlags flags);

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



