#include "add_node.h"

#include "imnodes/imnodes.h"


// Add
AddNode::AddNode(float x, float y)
	: Node("Add", x, y)
{
	
}

AddNode::~AddNode()
{
}

void AddNode::Create()
{
	AddPin(PinType::Input);
	AddPin(PinType::Input);
	AddPin(PinType::Output);

}



// Subtract 
SubtractNode::SubtractNode(float x, float y)
	: Node("Subtract", x, y)
{

}

SubtractNode::~SubtractNode()
{
}

void SubtractNode::Create()
{
	AddPin(PinType::Input);
	AddPin(PinType::Input);
	AddPin(PinType::Output);

}

// Multiply 
MultiplyNode::MultiplyNode(float x, float y)
	: Node("Multiply", x, y)
{

}

MultiplyNode::~MultiplyNode()
{
}

void MultiplyNode::Create()
{
	AddPin(PinType::Input);
	AddPin(PinType::Input);
	AddPin(PinType::Output);

}


// Divide 
DivideNode::DivideNode(float x, float y)
	: Node("Divide", x, y)
{

}

DivideNode::~DivideNode()
{
}

void DivideNode::Create()
{
	AddPin(PinType::Input);
	AddPin(PinType::Input);
	AddPin(PinType::Output);

}