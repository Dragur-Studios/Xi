#pragma once

#include "node.h"

class StartNode
    : public Node
{
public:
    StartNode(float x, float y);
    ~StartNode();

    virtual void OnCreateGUI() override;
    virtual void OnLink(Pin a, Pin b) override;
};
