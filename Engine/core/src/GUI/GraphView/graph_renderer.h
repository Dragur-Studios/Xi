#pragma once

#include "pch.h"
#include "defs.h"

struct Link
{
    int id;
    int start_attr, end_attr;
};

class GraphRenderer
{

public:
    GraphRenderer();
    ~GraphRenderer();

    void Update();
    void Render();

    template<class T>
    void AddNode(float x, float y);
    
    void AquirePins(const Link& link, struct Pin* a, struct Pin* b);

private:
    int current_id = 0;
    std::vector<struct Node*> nodes;
    std::vector<Link> links;
    
    struct ImNodesContext* context;
};

#include "graph_renderer.inl"
