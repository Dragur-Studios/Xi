#include "Node.h"

#include "imgui/imgui.h"
#include "imnodes/imnodes.h"

int Node::attr_id = 0;
int Node::node_id = 0;


void Node::Create(int input_pin_count, int output_pin_count)
{
	id = Node::CreateNodeID();

	for (int i = 0; i < input_pin_count; i++)
	{
		pins.push_back({ Node::CreateNodeID(), PinType::Input });
	}

	for (int i = 0; i < output_pin_count; i++)
	{
		pins.push_back({ Node::CreateNodeID(), PinType::Output });
	}


}

void Node::Draw()
{
	ImNodes::BeginNode(id);

	Render();

	ImNodes::EndNode();
}

void Node::DrawHeader(const std::string& caption)
{
	ImNodes::BeginNodeTitleBar();
	ImGui::Text(caption.c_str());
	ImNodes::EndNodeTitleBar();
}

void Node::DrawPins()
{
	for (const auto& pin : pins)
	{
		switch (pin.type)
		{
		case PinType::Input:
		{
			ImNodes::BeginInputAttribute(pin.id, ImNodesPinShape_::ImNodesPinShape_Circle);
			ImGui::TextUnformatted("Input");
			ImNodes::EndInputAttribute();
			break;
		}

		case PinType::Output:
		{
			ImNodes::BeginOutputAttribute(pin.id, ImNodesPinShape_::ImNodesPinShape_Circle);
			ImGui::TextUnformatted("Output");
			ImNodes::EndOutputAttribute();
			break;
		}
		}
	}
}


void TestNode::Render()
{
	DrawHeader("Test Node");
	DrawPins();
}
