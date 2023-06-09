#include "start_node.h"


StartNode::StartNode(float x, float y)
	: Node("Test Node", x, y)
{

}

StartNode::~StartNode()
{
}


void StartNode::OnCreateGUI()
{
	LOG_INFO("Creating Node!");

	AddPin(PinType::Output, PinClass::Float, PinFlags::NoEdit);

	LOG_INFO("Creating Test Node pin count: " + std::to_string(pins.size()));
}

void StartNode::OnLink(Pin a, Pin b)
{
}
