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

void AddNode::OnLink(Pin outputPin, Pin inputPin)
{
	inputPin.classification = outputPin.classification;
	inputPin.data = inputPin.data;
	
	switch (outputPin.classification)
	{
	case PinClass::Float:
		operation = [this]() {
			return this->AddAsFloat();
		};
		break;
	case PinClass::Float2:
		operation = [this]() {
			return this->AddAsFloat2();
		};
		break;
	case PinClass::Float3:
		operation = [this]() {
			return this->AddAsFloat3();
		};
		break;
	case PinClass::Float4:
		operation = [this]() {
			return this->AddAsFloat4();
		};
		break;
	}
}

void AddNode::OnCreateGUI()
{
	AddPin(PinType::Input, PinClass::Float);
	AddPin(PinType::Input, PinClass::Float);
	AddPin(PinType::Output, PinClass::Float);

}

void AddNode::AddAsFloat()
{
	float sum = 0;
	for (size_t i = 0; i < pins.size(); i++)
	{
		if (pins[i].type == PinType::Input) {
			sum += pins[i].data[0];
		}
	}

	for (size_t i = 0; i < pins.size(); i++)
	{
		if (pins[i].type == PinType::Output) {
			pins[i].data[0] = sum;
		}
	}

}

void AddNode::AddAsFloat2()
{
	float f1 = 0;
	float f2 = 0;
	for (size_t i = 0; i < pins.size(); i++)
	{
		if (pins[i].type == PinType::Input) {
			f1 += pins[i].data[0];
			f2 += pins[i].data[1];
		}
	}

	for (size_t i = 0; i < pins.size(); i++)
	{
		if (pins[i].type == PinType::Output) {
			pins[i].data[0] = f1;
			pins[i].data[1] = f2;
		}
	}
}

void AddNode::AddAsFloat3()
{
	float f1 = 0;
	float f2 = 0;
	float f3 = 0;
	for (size_t i = 0; i < pins.size(); i++)
	{
		if (pins[i].type == PinType::Input) {
			f1 += pins[i].data[0];
			f2 += pins[i].data[1];
			f3 += pins[i].data[2];
		}
	}

	for (size_t i = 0; i < pins.size(); i++)
	{
		if (pins[i].type == PinType::Output) {
			pins[i].data[0] = f1;
			pins[i].data[1] = f2;
			pins[i].data[2] = f3;
		}
	}
}

void AddNode::AddAsFloat4()
{
	float f1 = 0;
	float f2 = 0;
	float f3 = 0;
	float f4 = 0;
	for (size_t i = 0; i < pins.size(); i++)
	{
		if (pins[i].type == PinType::Input) {
			f1 += pins[i].data[0];
			f2 += pins[i].data[1];
			f3 += pins[i].data[2];
			f4 += pins[i].data[3];
		}
	}

	for (size_t i = 0; i < pins.size(); i++)
	{
		if (pins[i].type == PinType::Output) {
			pins[i].data[0] = f1;
			pins[i].data[1] = f2;
			pins[i].data[2] = f3;
			pins[i].data[3] = f4;
		}
	}
}



// Subtract 
SubtractNode::SubtractNode(float x, float y)
	: Node("Subtract", x, y)
{

}

SubtractNode::~SubtractNode()
{
}

void SubtractNode::OnLink(Pin outputPin, Pin inputPin)
{
	inputPin.classification = outputPin.classification;
	inputPin.data = inputPin.data;

}

void SubtractNode::OnCreateGUI()
{

	AddPin(PinType::Input, PinClass::Float);
	AddPin(PinType::Input, PinClass::Float);
	AddPin(PinType::Output, PinClass::Float);

}

// Multiply 
MultiplyNode::MultiplyNode(float x, float y)
	: Node("Multiply", x, y)
{

}

MultiplyNode::~MultiplyNode()
{
}

void MultiplyNode::OnLink(Pin outputPin, Pin inputPin)
{
	inputPin.classification = outputPin.classification;
	inputPin.data = inputPin.data;


}

void MultiplyNode::OnCreateGUI()
{
	AddPin(PinType::Input, PinClass::Float);
	AddPin(PinType::Input, PinClass::Float);
	AddPin(PinType::Output, PinClass::Float);

}


// Divide 
DivideNode::DivideNode(float x, float y)
	: Node("Divide", x, y)
{

}

DivideNode::~DivideNode()
{
}

void DivideNode::OnLink(Pin outputPin, Pin inputPin)
{
	inputPin.classification = outputPin.classification;
	inputPin.data = inputPin.data;
}

void DivideNode::OnCreateGUI()
{

	AddPin(PinType::Input, PinClass::Float);
	AddPin(PinType::Input, PinClass::Float);
	AddPin(PinType::Output, PinClass::Float);
}