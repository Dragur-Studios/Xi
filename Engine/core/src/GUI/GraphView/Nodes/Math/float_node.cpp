#include "float_node.h"

#include "GUI/GraphView/Pins/Pin.h"

FloatNode::FloatNode(int x, int y)
	: Node("Float", x, y,  0xFFFF1616)
{
	
}

FloatNode::~FloatNode()
{
}

void FloatNode::OnCreateGUI()
{
	AddPin(PinType::Output, PinClass::Float, PinFlags::None);
}

void FloatNode::OnLink(Pin outputPin, Pin inputPin)
{/*NO LINK*/
}

// FLOAT 2

Float2Node::Float2Node(int x, int y)
	: Node("Float2", x, y, 0xFFFF1616)
{

}

Float2Node::~Float2Node()
{
}

void Float2Node::OnCreateGUI()
{
	AddPin(PinType::Output, PinClass::Float2, PinFlags::None);
}

void Float2Node::OnLink(Pin outputPin, Pin inputPin)
{/*NO LINK*/}

// FLOAT 3

Float3Node::Float3Node(int x, int y)
	: Node("Float3", x, y, 0xFFFF1616)
{

}

Float3Node::~Float3Node()
{
}

void Float3Node::OnCreateGUI()
{
	AddPin(PinType::Output, PinClass::Float3, PinFlags::None);

}

void Float3Node::OnLink(Pin outputPin, Pin inputPin)
{/*NO LINK*/
}


// FLOAT 4

Float4Node::Float4Node(int x, int y)
	: Node("Float4", x, y, 0xFFFF1616)
{

}

Float4Node::~Float4Node()
{
}

void Float4Node::OnCreateGUI()
{
	AddPin(PinType::Output, PinClass::Float4, PinFlags::None);
}

void Float4Node::OnLink(Pin outputPin, Pin inputPin)
{/*NO LINK*/
}
