#include "graph_renderer.h"


#include "graph_view.h"
//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtc/matrix_inverse.hpp"
//#include "glm/gtx/matrix_decompose.hpp"
//


#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include "imnodes/imnodes.h"


#include "nodes.h"


GraphRenderer::GraphRenderer()
{

    context = ImNodes::CreateContext();

    ImNodesIO& io = ImNodes::GetIO();
    io.EmulateThreeButtonMouse.Modifier = &ImGui::GetIO().KeyAlt;

 
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

    for (int i = 0; i < links.size(); ++i)
    {
        const std::pair<int, int> p = links[i];
        ImNodes::Link(i, p.first, p.second);
    }
    
    ImNodes::EndNodeEditor();

    // link detection
    int start_attr, end_attr;
    if (ImNodes::IsLinkCreated(&start_attr, &end_attr))
    {
        links.push_back(std::make_pair(start_attr, end_attr));
    }

    // selection detection
    const int num_selected_nodes = ImNodes::NumSelectedNodes();
    if (num_selected_nodes > 0)
    {
        std::vector<int> selected_nodes;
        selected_nodes.resize(num_selected_nodes);
        ImNodes::GetSelectedNodes(selected_nodes.data());
    }

}


