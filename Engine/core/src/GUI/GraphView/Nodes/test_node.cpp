#include "test_node.h"


TestNode::TestNode(float x, float y)
	: Node("Test Node", x, y)
{

}

TestNode::~TestNode()
{
}


void TestNode::Create()
{
	LOG_INFO("Creating Node!");

	AddPin(PinType::Input);
	AddPin(PinType::Output);
	AddPin(PinType::Output);


	LOG_INFO("Creating Test Node pin count: " + std::to_string(pins.size()));
}
