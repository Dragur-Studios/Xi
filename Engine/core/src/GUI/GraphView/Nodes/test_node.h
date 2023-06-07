#pragma once

#include "node.h"

class TestNode
    : public Node
{
public:
    TestNode(float x, float y);
    ~TestNode();

    virtual void Create() override;
};
