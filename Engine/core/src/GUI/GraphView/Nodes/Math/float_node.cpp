#include "float_node.h"

FloatNode::FloatNode(int x, int y)
	: Node("Float", x, y,  0xFFFF1616)
{
	
}

FloatNode::~FloatNode()
{
}

void FloatNode::Create()
{
	AddPin(PinType::Output);
}

// FLOAT 2

Float2Node::Float2Node(int x, int y)
	: Node("Float2", x, y, 0xFFFF1616)
{

}

Float2Node::~Float2Node()
{
}

void Float2Node::Create()
{
	AddPin(PinType::Output);
}

// FLOAT 3

Float3Node::Float3Node(int x, int y)
	: Node("Float3", x, y, 0xFFFF1616)
{

}

Float3Node::~Float3Node()
{
}

void Float3Node::Create()
{
	AddPin(PinType::Output);
}


// FLOAT 4

Float4Node::Float4Node(int x, int y)
	: Node("Float4", x, y, 0xFFFF1616)
{

}

Float4Node::~Float4Node()
{
}

void Float4Node::Create()
{
	AddPin(PinType::Output);
}