#pragma once

#include "graph_renderer.h"
#include "imnodes/imnodes.h"

template<class T>
void GraphRenderer::AddNode(float x, float y)
{
    T* node = new T(x, y);

    node->OnCreateGUI();

    ImNodes::SetNodeScreenSpacePos(node->id, ImVec2(x, y));
    ImNodes::SnapNodeToGrid(node->id);

    nodes.push_back(node);

    LOG_SUCCESS("Node Created!");
}