#include "add_node.h"

#include "imnodes/imnodes.h"

#include "gui/graphview/pins/pin.h"

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
	AddPin(PinType::Input, PinClass::Float, PinFlags::None);
	AddPin(PinType::Input, PinClass::Float, PinFlags::None);
	AddPin(PinType::Output, PinClass::Float, PinFlags::None);

}

void AddNode::AddAsFloat()
{
	float* buffer = (float*)calloc(1, sizeof(float));
	
	if (buffer == nullptr)
		return;

	for (size_t i = 0; i < pins.size(); i++)
	{
		auto temp = (float*)(pins[i].data);
		if (pins[i].type == PinType::Input) {
			*buffer += *temp;
		}
	}

	for (size_t i = 0; i < pins.size(); i++)
	{
		if (pins[i].type == PinType::Output) {
			pins[i].data = (void*)buffer;
		}
	}

	free(buffer);

}

void AddNode::AddAsFloat2()
{
	float* buffer= (float*)calloc(2, sizeof(float));

	if (buffer == nullptr)
		return;

	for (size_t i = 0; i < pins.size(); i++)
	{
		if (pins[i].type == PinType::Input) {
			for (size_t j = 0; j < 2; j++)
			{
				buffer[i] += ((float*)(pins[i].data))[i];
			}
		}
	}

	for (size_t i = 0; i < pins.size(); i++)
	{
		if (pins[i].type == PinType::Output) {
			pins[i].data = (void*)buffer;
		}
	}

	free(buffer);
}

void AddNode::AddAsFloat3()
{
	float* buffer = (float*)calloc(3, sizeof(float));
	
	if (buffer == nullptr)
		return;
	
	for (size_t i = 0; i < pins.size(); i++)
	{
		if (pins[i].type == PinType::Input) {
			for (size_t j = 0; j < 3; j++)
			{
				buffer[i] += ((float*)(pins[i].data))[i];
			}
		}
	}

	for (size_t i = 0; i < pins.size(); i++)
	{
		if (pins[i].type == PinType::Output) {
			pins[i].data = (void*)buffer;
		}
	}

	free(buffer);
}

void AddNode::AddAsFloat4()
{
	float* buffer = (float*)calloc(2, sizeof(float));

	if (buffer == nullptr)
		return;

	for (size_t i = 0; i < pins.size(); i++)
	{
		if (pins[i].type == PinType::Input) {
			for (size_t j = 0; j < 2; j++)
			{
				buffer[i] += ((float*)(pins[i].data))[i];
			}
		}
	}

	for (size_t i = 0; i < pins.size(); i++)
	{
		if (pins[i].type == PinType::Output) {
			pins[i].data = (void*)buffer;
		}
	}

	free(buffer);
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

	AddPin(PinType::Input, PinClass::Float, PinFlags::None);
	AddPin(PinType::Input, PinClass::Float, PinFlags::None);
	AddPin(PinType::Output, PinClass::Float, PinFlags::None);

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
	AddPin(PinType::Input, PinClass::Float, PinFlags::None);
	AddPin(PinType::Input, PinClass::Float, PinFlags::None);
	AddPin(PinType::Output, PinClass::Float, PinFlags::None);

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

	AddPin(PinType::Input, PinClass::Float, PinFlags::None);
	AddPin(PinType::Input, PinClass::Float, PinFlags::None);
	AddPin(PinType::Output, PinClass::Float, PinFlags::None);
}