#include "graph_renderer.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include "graph_view.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtx/matrix_decompose.hpp"


std::string glm_mat_as_string(glm::mat4x4 matrix){
std::stringstream ss;
ss << "{\n";
for (size_t i = 0; i < 4; i++) { for (size_t j = 0; j < 4; j++) { ss << matrix[i][j] << ", "; } ss << "\n";} 
ss << "}\n";
return ss.str();}



GraphRenderer::GraphRenderer()
    :cameraMatrix{glm::mat4(1.0f)}
{
    //BuildBackgroundGrid(ImGui::GetWindowPos(), ImGui::GetWindowSize());
}


void GraphRenderer::DrawGrid()
{
    ImU32 color1 = 0xFF161616;
    ImU32 color2 = 0xFF323232;

    // draw horizontal lines

    // draw vertical lines


}


void GraphRenderer::Update()
{
    //const vec2 currentCameraPos = vec2(screenMatrix[3][0], screenMatrix[3][1]);

    //if (currentCameraPos != prevCameraPos) {
    //    vec2 deltaPos = currentCameraPos - prevCameraPos;

    //    // Update the positions of all nodes
    //    for (auto node : nodes) {
    //        node->position += deltaPos;
    //    }

    //    // Update the positions of all lines
    //    for (auto& line : grid) {
    //        line.start += deltaPos;
    //        line.end += deltaPos;
    //    }

    //    prevCameraPos = currentCameraPos;
    //}


    //const vec2 currentWPos = to_glm_vec(ImGui::GetWindowPos());

    //if (currentWPos != prevWPos) {

    //    vec2 deltaPos = (currentWPos - prevWPos);
    //    // Update the positions of all nodes
    //    for (auto node : nodes) {

    //        node->position += deltaPos;
    //    }

    //    // Update the positions of all grid lines
    //    for (auto& line : grid) {
    //        line.start += deltaPos;
    //        line.end += deltaPos;
    //    }

    //    // Rebuild the background grid
    //    BuildBackgroundGrid(ImGui::GetWindowPos(), ImGui::GetWindowSize());
    // 
    //    prevWPos = currentWPos;
    //}

    projectionMatrix = glm::orthoLH(-1.0f, 1.0f, -1.0f, 1.0f, 0.01f, 100.0f);
    viewMatrix = glm::inverse(cameraMatrix);

    LOG_INFO("<View>: " + glm_mat_as_string(viewMatrix));
    LOG_INFO("<Projection>: " + glm_mat_as_string(projectionMatrix));


}

void  GraphRenderer::DrawLine(const Line& line)
{
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    vec2 windowPos = to_glm_vec(ImGui::GetWindowPos());
    vec2 cameraPosition = GetOriginOffset();
    vec2 screenSize = to_glm_vec(ImGui::GetWindowSize());
    auto z =  GetZoom();

    vec4 start = line.matrix * vec4(0.5f, 0.0f, 0.0f, 1.0f);
    vec4 end = line.matrix * vec4(0.5f, 1.0f, 0.0f, 1.0f);

    vec2 p1 = (cameraPosition + (windowPos + vec2(start) * screenSize)) / z; // NDC coordinate scaled to window size
    vec2 p2 = (cameraPosition + (windowPos + vec2(end) * screenSize)) / z; // NDC coordinate scaled to window size

    drawList->AddLine(to_im_vec(p1), to_im_vec(p2), line.color, line.thickness);
}


void GraphRenderer::DrawNode(const Node& node) 
{
    //ImDrawList* drawList = ImGui::GetWindowDrawList();
    
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    vec2 windowPos = to_glm_vec(ImGui::GetWindowPos());
    vec2 cameraPosition = GetOriginOffset();
    vec2 screenSize = to_glm_vec(ImGui::GetWindowSize());
    auto z = GetZoom();

    float width = node.matrix[0][0];
    float height = node.matrix[1][1];
    
    vec2 center = vec2(node.matrix[3][0], node.matrix[3][1]);

    vec2 half_extents = vec2(width, height) * 0.5f;

    vec2 tl = vec2(center.x - half_extents.x , center.y - half_extents.y);
    vec2 bl = vec2(center.x - half_extents.x , center.y + half_extents.y);
    vec2 br = vec2(center.x + half_extents.x , center.y + half_extents.y);
    vec2 tr = vec2(center.x + half_extents.x , center.y - half_extents.y);
    
    LOG_INFO("NODE MATRIX: " + glm_mat_as_string(node.matrix));

    //auto mvp = projectionMatrix * viewMatrix * node.matrix;

    vec4 p1_ndc = node.matrix * vec4(br, 0.0f, 1.0f);
    vec4 p2_ndc = node.matrix * vec4(bl, 0.0f, 1.0f);
    vec4 p3_ndc = node.matrix * vec4(tl, 0.0f, 1.0f);
    vec4 p4_ndc = node.matrix * vec4(tr, 0.0f, 1.0f);

    vec2 p1 = (cameraPosition + (windowPos + vec2(p1_ndc) * screenSize)) / z; // NDC coordinate scaled to window size
    vec2 p2 = (cameraPosition + (windowPos + vec2(p2_ndc) * screenSize)) / z; // NDC coordinate scaled to window size
    vec2 p3 = (cameraPosition + (windowPos + vec2(p3_ndc) * screenSize)) / z; // NDC coordinate scaled to window size
    vec2 p4 = (cameraPosition + (windowPos + vec2(p4_ndc) * screenSize)) / z; // NDC coordinate scaled to window size


    drawList->AddQuadFilled(to_im_vec(p1), to_im_vec(p2), to_im_vec(p3), to_im_vec(p4), (ImU32)0xFF242424);



    // Draw the node label
    ImVec2 labelSize = ImGui::CalcTextSize(node.label.c_str());
    ImVec2 labelPos = ImVec2(center.x - labelSize.x * 0.5f, center.y - labelSize.y * 0.5f);
    //ImVec2 labelPos = to_im_vec(center);
    drawList->AddText(labelPos, IM_COL32(0, 0, 0, 255), node.label.c_str());
}


void GraphRenderer::Render()
{
    
    if (!Begin()) return;


    
  
    //vec2 p3 = originOffset + (vec2(0.5f, 0.8f) * canvasSize) * zoom; // NDC coordinate scaled to window size
    
    ImColor color = ImColor(0, 255, 0); // Green color
    float thickness = 1.0f;
    
    //DrawGrid();


    for (auto node : nodes)
    {
        DrawNode(*node);
    }

    // Render connections
    for (const auto& c : connections)
    {
        // Render the connection using the renderer
        DrawConnection(c.input, c.output, ImColor(255, 255, 255));
    }

#if 1
    Line line;
    line.color = 0xFFFFFFFF;
    line.thickness = 1.0f;

    mat4x4 modelMatrix = mat4(1.0f);
    line.matrix = projectionMatrix * viewMatrix * modelMatrix;

    DrawLine(line);


    Node node{};
    node.matrix = modelMatrix;
    node.label = "Tester";

    DrawNode(node);

#endif   
    End();

}


void GraphRenderer::AddNode(Node* node)
{
    nodes.push_back(node);
   /* auto model = node->matrix;
    
    node->matrix = projectionMatrix * viewMatrix * model;*/

    LOG_INFO("NodeCount: " + std::to_string(nodes.size()));

}

void GraphRenderer::AddConnection(Node* node1, Node* node2)
{
    Connection c;
    c.input = node1;
    c.output = node2;

    connections.push_back(c);
}

vec2 GraphRenderer::GetOriginOffset()
{
    return vec2(cameraMatrix[3][0], cameraMatrix[3][1]);
}

void GraphRenderer::UpdateScreenOffset(vec2 offset)
{
    cameraMatrix[3][0] = offset.x;
    cameraMatrix[3][1] = offset.y;
}

float GraphRenderer::GetZoom()
{
    return zoom;
}

void GraphRenderer::UpdateZoom(float value)
{
    zoom = value;
}

bool GraphRenderer::Begin()
{
    if (!ImGui::BeginChild("##GV_RENDERER")) {
        ImGui::End();
        return false;
    }

    drawList = ImGui::GetWindowDrawList();

    return true;
}

void GraphRenderer::End()
{
    ImGui::EndChild();
}

//void GraphRenderer::DrawNode(Node* node)
//{
//    ImDrawList* drawList = ImGui::GetWindowDrawList();
//    vec2 windowPos = to_glm_vec(ImGui::GetWindowPos());
//    vec2 originOffset = GetOriginOffset();
//    auto z = GetZoom();
//    vec2 canvasSize = to_glm_vec(ImGui::GetWindowSize());
//
//    // Calculate the screen position of the node using the NDC trick
//    
//    //vec2 center = (originOffset + (windowPos + vec2(node->position) * canvasSize)) / z;
//    vec2 center = node->position;
//    // Calculate the screen size of the node
//    vec2 screenSize = node->size / z;
//
//    // Draw the node background
//    drawList->AddRectFilled(to_im_vec(vec2(center - screenSize * 0.5f)), to_im_vec((center + screenSize * 0.5f)), IM_COL32(255, 255, 255, 255));
//
//    std::string posStr = "position: (" + std::to_string(node->position.x) + ", " + std::to_string(node->position.y) + ")";
//    std::string sizeStr = "size: (" + std::to_string(node->size.x) + ", " + std::to_string(node->size.y) + ")";
//    LOG_INFO("Drawing Node: " + posStr + sizeStr );
//

//}

void GraphRenderer::DrawConnection(Node* nodeA, Node* nodeB, unsigned int color)
{
  /*  vec2 p2(nodeA->position.x + 150, -100);
    vec2 p3(nodeB->position.x + 50, 0);



    drawList->AddBezierCurve(to_im_vec(nodeA->position), to_im_vec(p2), to_im_vec(p3), to_im_vec(nodeB->position), (ImU32)color, 2.0f);*/

}

vec2 GraphRenderer::ScreenToWorldPosition(const vec2& screenPos)
{
    // Get the window position and size
    vec2 windowPos = to_glm_vec(ImGui::GetWindowPos());
    vec2 windowSize = to_glm_vec(ImGui::GetWindowSize());

    // Calculate the canvas size
    vec2 canvasSize = windowSize / GetZoom();

    // Adjust the screen position with the origin offset
    vec2 adjustedScreenPos = vec2(screenPos.x, windowSize.y - screenPos.y) - GetOriginOffset();

    // Convert the screen position to normalized device coordinates (NDC)
    vec2 ndc = (adjustedScreenPos / canvasSize) * 2.0f - 1.0f;

    // Apply the inverse view and projection matrices to get the world position
    mat4 inverseVP = glm::inverse(projectionMatrix * viewMatrix);
    vec4 worldPos = inverseVP * vec4(ndc.x, ndc.y, 0.0f, 1.0f);
    worldPos /= worldPos.w;

    return vec2(worldPos);
}

vec2 GraphRenderer::WorldToScreenPosition(const vec2& worldPos)
{
    // Get the window position and size
    vec2 windowPos = to_glm_vec(ImGui::GetWindowPos());
    vec2 windowSize = to_glm_vec(ImGui::GetWindowSize());

    // Calculate the canvas size
    vec2 canvasSize = windowSize / GetZoom();

    // Apply the view and projection matrices to get the clip space position
    vec4 clipPos = projectionMatrix * viewMatrix * vec4(worldPos, 0.0f, 1.0f);

    // Perform the perspective division to obtain normalized device coordinates (NDC)
    vec2 ndc = vec2(clipPos) / clipPos.w;

    // Scale and offset the NDC coordinates to match the canvas size and origin
    vec2 adjustedScreenPos = ((ndc + 1.0f) * 0.5f) * canvasSize + GetOriginOffset();

    // Convert the adjusted screen position to screen coordinates
    vec2 screenPos = vec2(adjustedScreenPos.x, windowSize.y - adjustedScreenPos.y);

    return screenPos;
}


void GraphRenderer::UpdateCameraMatrix(glm::vec2 cameraPos, float zoom)
{
   
}

bool GraphRenderer::IsLineVisible(Line line, const ImVec2& visibleRegionMin, const ImVec2& visibleRegionMax)
{
    //// Check if any part of the line is within the visible region
    //return (line.start.x >= visibleRegionMin.x && line.start.x <= visibleRegionMax.x) ||
    //    (line.end.x >= visibleRegionMin.x && line.end.x <= visibleRegionMax.x) ||
    //    (line.start.y >= visibleRegionMin.y && line.start.y <= visibleRegionMax.y) ||
    //    (line.end.y >= visibleRegionMin.y && line.end.y <= visibleRegionMax.y);
    return false;
}


