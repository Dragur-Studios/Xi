#pragma once

#include "pch.h"
#include "defs.h"

class GraphRenderer
{

public:
    GraphRenderer();
    ~GraphRenderer();

    void Update();
    void Render();

    void AddNode(float x, float y);
    
private:
    std::vector<struct Node*> nodes;
    struct ImNodesContext* context;
};
