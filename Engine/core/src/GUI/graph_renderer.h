#pragma once

#include "pch.h"
#include "defs.h"


#include "glm/glm.hpp"

using namespace glm;


struct Line {
    mat4x4 matrix;

    unsigned int color = 0xFF'FF'FF'FF;
    float thickness = 1.0f;
};

struct Node {
    std::string label;
    
    mat4x4 matrix;
     
    std::vector<Node*> inputs;
    std::vector<Node*> outputs;

};


struct Connection {
    Node* input;
    Node* output;
};


class GraphRenderer
{

public:
    GraphRenderer();

    void Update();
    void Render();

    void AddNode(Node* node);
    void AddConnection(struct Node* node1, struct Node* node2);

    vec2 GetOriginOffset();
    void UpdateScreenOffset(vec2 offset);

    float GetZoom();
    void UpdateZoom(float value);

    vec2 ScreenToWorldPosition(const vec2& screenPos);
    vec2 WorldToScreenPosition(const vec2& worldPos);

private:
    void DrawLine(const Line& line);
    
    void DrawGrid();



    bool Begin();
    void End();
    void DrawNode(const struct Node& node);
    void DrawConnection(struct Node* nodeA, struct Node* nodeB, unsigned int color);

    void UpdateCameraMatrix(vec2 cameraPos, float zoom);
    bool IsLineVisible(Line line, const struct ImVec2& visibleMin, const struct ImVec2& visibleRegion);

private:
    // state
    vec2 prevWPos;
    vec2 prevCameraPos;

    struct ImDrawList* drawList;

    mat4x4 cameraMatrix;

    // data
    std::vector<Line> grid;
    std::vector<Node*> nodes;
    std::vector<Connection> connections;
    
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    

    float zoom = 1.0f;

};
