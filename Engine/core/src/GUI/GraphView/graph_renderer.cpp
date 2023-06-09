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
    
    
    for (const auto& node : nodes)
    {
        node->Update();
    }
    

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
        std::pair<Pin*, Pin*> p = links[i];
        // pass the data through the graph
        p.second->data = p.first->data;

        ImNodes::Link(i, p.first->id, p.second->id);
    }
    
    ImNodes::EndNodeEditor();

    // link detection
    //Pin start_attr, end_attr;
    int output_id, input_id;
    if (ImNodes::IsLinkCreated(&output_id, &input_id))
    {
        // on link
        
        Node* outputNode = nullptr;
        Node* inputNode = nullptr;
        Pin* outputPin = nullptr;
        Pin* inputPin = nullptr;

        for (size_t i = 0; i < nodes.size(); i++)
        {

            for (size_t j = 0; j < nodes[i]->pins.size(); j++)
            {
                if (nodes[i]->pins[j].id == output_id) {
                    outputNode = nodes[i];
                    outputPin = &nodes[i]->pins[j];
                }
                else if (nodes[i]->pins[j].id == input_id) {
                    inputNode = nodes[i];
                    inputPin = &nodes[i]->pins[j];
                }

            }
        }

        if (inputPin != nullptr && outputPin != nullptr) {
            
            inputPin->data = outputPin->data;

            outputNode->OnLink(*outputPin, *inputPin);


        }
        else {
            LOG_ERROR("Coulr Not Find Pin");
        }

        //end_attr.value = start_attr.value;
        
        LOG_INFO("ON LINK!");

        links.push_back(std::make_pair(outputPin, inputPin));
    }

    const int num_selected_links = ImNodes::NumSelectedLinks();
    if (num_selected_links > 0)
    {
        std::vector<int> selected_links;
        selected_links.resize(num_selected_links);
        ImNodes::GetSelectedLinks(selected_links.data());
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


