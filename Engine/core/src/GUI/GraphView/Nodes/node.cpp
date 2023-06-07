#include "node.h"

#include "imgui/imgui.h"
#include "imnodes/imnodes.h"

int Node::attr_id = 0;
int Node::node_id = 0;


Node::Node(const std::string& title, float x, float y)
	: title{ title }, position{ x, y }, id{ CreateNodeID() }
{

}

Node::~Node()
{
}


void Node::Draw()
{
	ImNodes::BeginNode(id);
	DrawTitleBox();
	DrawPins();
	ImNodes::EndNode();
}

void Node::DrawTitleBox()
{
	ImNodes::BeginNodeTitleBar();
	ImGui::Text(title.c_str());
	ImNodes::EndNodeTitleBar();
}

void Node::DrawPins()
{

	for (const auto& pin : pins)
	{
		if (pin.type == PinType::Input) {
			ImNodes::BeginInputAttribute(pin.id, ImNodesPinShape_::ImNodesPinShape_Circle);
			ImGui::TextUnformatted("Input");
			ImNodes::EndInputAttribute();
		}
		if (pin.type == PinType::Output) {
			ImNodes::BeginOutputAttribute(pin.id, ImNodesPinShape_::ImNodesPinShape_Circle);
			ImGui::TextUnformatted("Output");
			ImNodes::EndOutputAttribute();
		}

	}


}

void Node::AddPin(PinType type)
{
	LOG_INFO("Adding Pin");

	Pin p = Pin();
	p.type = type;
	p.id = CreateAttributeID();

	pins.push_back(p);
}




