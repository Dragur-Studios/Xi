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

    template<class T>
    void AddNode(float x, float y);
    
private:
    std::vector<struct Node*> nodes;
    std::vector<std::pair<struct Pin*, struct Pin*>> links;

    struct ImNodesContext* context;
};

#include "graph_renderer.inl"
