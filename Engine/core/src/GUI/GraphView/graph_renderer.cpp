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
#include "Pins/Pin.h"

GraphRenderer::GraphRenderer()
{

    context = ImNodes::CreateContext();

    ImNodesIO& io = ImNodes::GetIO();
    io.EmulateThreeButtonMouse.Modifier = &ImGui::GetIO().KeyAlt;
    ImNodes::GetIO().LinkDetachWithModifierClick.Modifier = &ImGui::GetIO().KeyCtrl;
    ImNodes::PushAttributeFlag(ImNodesAttributeFlags_EnableLinkDetachWithDragClick);
 
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

template <typename T>
void deleteElements(std::vector<std::pair<Pin*,Pin*>>& targetList, const std::vector<int>& selectedIDs)
{
    std::vector<int> deleteList;

    // Step 2: Search for elements based on selected IDs
    for (int selectedID : selectedIDs)
    {
        auto it = std::find_if(targetList.begin(), targetList.end(), [selectedID](const T& element) {
            // Modify the condition to match the comparison with the ID in your target list
            return element.getID() == selectedID;
            });

        if (it != targetList.end())
        {
            // Add the index or reference to the element to the delete list
            int index = std::distance(targetList.begin(), it);
            deleteList.push_back(index);
        }
    }

    // Step 3: Delete elements from the target list
    for (auto it = deleteList.rbegin(); it != deleteList.rend(); ++it)
    {
        targetList.erase(targetList.begin() + *it);
    }
}


   //end_attr.value = start_attr.value;
void GraphRenderer::AquirePins(const Link& link, Pin* output, Pin* input)
{
    Node* outputNode = nullptr;
    Node* inputNode = nullptr;

    for (size_t i = 0; i < nodes.size(); i++)
    {
        for (size_t j = 0; j < nodes[i]->pins.size(); j++)
        {
            if (nodes[i]->pins[j].id == link.start_attr) {
                outputNode = nodes[i];
                output = &nodes[i]->pins[j];
            }
            else if (nodes[i]->pins[j].id == link.end_attr) {
                inputNode = nodes[i];
                input = &nodes[i]->pins[j];
            }

        }
    }

    if (input != nullptr && output != nullptr) {

        input->data = output->data;

        outputNode->OnLink(*output, *input);


    }
    else {
        LOG_ERROR("Coulr Not Find Pin");
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
        Link p = links[i];
        ImNodes::Link(p.id, p.start_attr, p.end_attr);
    }
    
    ImNodes::EndNodeEditor();

    // link detection
    {

        Link link{};
        if (ImNodes::IsLinkCreated(&link.start_attr, &link.end_attr))
        {
     
            Pin* inputPin = nullptr;
            Pin* outputPin = nullptr;

            AquirePins(link, outputPin, inputPin);
			
            link.id = ++current_id;
            links.push_back(link);
        }

    }
    {

        //const int num_selected_links = ImNodes::NumSelectedLinks();
        //if (num_selected_links > 0)
        //{
        //    std::vector<int> selected_links;
        //    selected_links.resize(num_selected_links);
        //    ImNodes::GetSelectedLinks(selected_links.data());

        //    if (ImGui::IsKeyReleased(ImGuiKey_::ImGuiKey_Delete)) {
        //        // Step 2: Search for elements based on selected IDs
        //        for (size_t i = 0; i < selected_links.size(); i++)
        //        {
        //            auto it = links.begin() + selected_links[i];
        //            if (ImNodes::IsLinkDestroyed(&selected_links[i])) {
        //                links.erase(it);
        //            }

        //        }
        //    }

        //}
    }

    // link stuff
    {
        int link_id;
        if (ImNodes::IsLinkDestroyed(&link_id))
        {

            auto iter =
                std::find_if(links.begin(), links.end(), [link_id](const Link& link) -> bool {
                return link.id == link_id;
                    });
            assert(iter != links.end());
            
            Pin* inputPin = nullptr;
            Pin* outputPin = nullptr;
            AquirePins(links[link_id], outputPin, inputPin);

            inputPin->data = 0;

            links.erase(iter);
        }
    }
    {
        int link_id;
        if (ImNodes::IsLinkDropped(&link_id))
        {

            auto iter =
                std::find_if(links.begin(), links.end(), [link_id](const Link& link) -> bool {
                return link.id == link_id;
                    });
            assert(iter != links.end());

            Pin* inputPin = nullptr;
            Pin* outputPin = nullptr;
            AquirePins(links[link_id], outputPin, inputPin);

            inputPin->data = 0;

            links.erase(iter);
        }
    }

   

    // node selection detection
    const int num_selected_nodes = ImNodes::NumSelectedNodes();
    if (num_selected_nodes > 0)
    {
        std::vector<int> selected_nodes;
        selected_nodes.resize(num_selected_nodes);
        ImNodes::GetSelectedNodes(selected_nodes.data());
    }

}


