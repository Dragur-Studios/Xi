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

    Node(float x, float y) : position{ x, y }, id{ 0 } {}

    void Create(int input_pin_count = 0, int output_pin_count = 0);
    void Draw();

    std::vector<Pin> pins;
    int id;
    struct {
        float x;
        float y;
    }position;

protected:
    
    virtual void Render() = 0;

    static int CreateNodeID() { return node_id++; }
    static int CreateAttributeID() { return attr_id++; }

    void DrawHeader(const std::string& caption);
    void DrawPins();

 
// STATIC HELPERS 
protected:

    static int AddPin(Node* node, PinType type) {
        node->pins.push_back({ CreateAttributeID(), type,});
    }
private:
    static int node_id; // max nodes = 2,147,483,647
    static int attr_id; // max attributes = 2,147,483,647
};


struct TestNode 
    : public Node {
    TestNode(float x, float y) : Node(x, y){}
    virtual void Render() override;
};
