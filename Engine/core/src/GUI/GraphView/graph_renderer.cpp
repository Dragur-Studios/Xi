#include "graph_renderer.h"


#include "graph_view.h"
//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtc/matrix_inverse.hpp"
//#include "glm/gtx/matrix_decompose.hpp"
//


#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "imnodes/imnodes.h"


#include "node.h"


GraphRenderer::GraphRenderer()
{

    context = ImNodes::CreateContext();
 
}

GraphRenderer::~GraphRenderer() {
    
    ImNodes::DestroyContext(context);
}


void GraphRenderer::Update()
{
    
    

    

}

 

void GraphRenderer::Render()
{
    
    auto& colors = ImNodes::GetStyle().Colors;
    colors[ImNodesCol_::ImNodesCol_GridBackground] = 0xFF161616;
    colors[ImNodesCol_::ImNodesCol_GridLine] = 0xFF242424;
    colors[ImNodesCol_::ImNodesCol_GridLinePrimary] = 0xFF484848;

    ImNodes::GetStyle().Flags |= ImNodesStyleFlags_GridLinesMultipleSizes;

    ImNodes::BeginNodeEditor();
    
    for (const auto& node : nodes)
    {
        node->Draw();
    }
    
    
    ImNodes::EndNodeEditor();

}

void GraphRenderer::AddNode(float x, float y)
{
    
    auto node = new TestNode(x, y);

    node->Create();

    ImNodes::SetNodeScreenSpacePos(node->id, ImVec2(x, y));
    ImNodes::SnapNodeToGrid(node->id);

    nodes.push_back(node);
}
