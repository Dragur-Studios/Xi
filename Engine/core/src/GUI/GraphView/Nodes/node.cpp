#include "node.h"

#include "imgui/imgui.h"
#include "imnodes/imnodes.h"

int Node::attr_id = 0;
int Node::node_id = 0;


Node::Node(const std::string& title, float x, float y, unsigned int title_color)
	: title{ title }, position{ x, y }, id{ CreateNodeID() }, title_bar_color{title_color}
{
	title_bar_color_hvr = title_color * 1.25f;

}

Node::~Node()
{
}


void Node::Update()
{
	if (operation != nullptr) {
		operation();
	}
}

void Node::Draw()
{
	ImNodes::PushColorStyle(ImNodesCol_::ImNodesCol_TitleBar, title_bar_color);

	ImNodes::BeginNode(id);
	DrawTitleBox();
	DrawPins();
	ImNodes::EndNode();

	ImNodes::PopColorStyle();

}

void Node::DrawTitleBox()
{
	ImNodes::BeginNodeTitleBar();
	ImGui::Text(title.c_str());
	ImNodes::EndNodeTitleBar();
}

void Node::DrawPins()
{

	for (auto& pin : pins)
	{
		if (pin.type == PinType::Input) {
			ImNodes::BeginInputAttribute(pin.id, ImNodesPinShape_::ImNodesPinShape_Circle);

			if (pin.flags == PinFlags::NoEdit) {
				ImGui::Text("%.00f", pin.data);
			}
			else
			{
				float data = 0;
				ImGui::SetNextItemWidth(150.0f);
				switch (pin.classification)
				{
					case PinClass::Float:
					{
						ImGui::InputFloat("Input", pin.data, 0.1f, 0.5f, "%.00f");
						break;
					}
					case PinClass::Float2:
					{
						ImGui::InputFloat2("Input", pin.data, "%.00f");
						break;
					}
					case PinClass::Float3:
					{
						ImGui::InputFloat3("Input", pin.data, "%.00f");
						break;
					}
					case PinClass::Float4:
					{
						ImGui::InputFloat4("Input", pin.data, "%.00f");
						break;
					}
				}
			}


			ImNodes::EndInputAttribute();
		}
	}
	
	ImGui::Dummy({ 40.0f, 40.0f });

	for (auto& pin : pins)
	{
		if (pin.type == PinType::Output) {
			ImNodes::BeginOutputAttribute(pin.id, ImNodesPinShape_::ImNodesPinShape_Circle);
			
			if (pin.flags == PinFlags::NoEdit) {
				ImGui::Text("%.00f", pin.data);
			}
			else 
			{
				ImGui::SetNextItemWidth(150.0f);
				switch (pin.classification)
				{
					case PinClass::Float:
					{
						ImGui::InputFloat("Input", pin.data, 0.1f, 0.5f, "%.00f");
						break;
					}
					case PinClass::Float2:
					{
						ImGui::InputFloat2("Input", pin.data, "%.00f");
						break;
					}
					case PinClass::Float3:
					{
						ImGui::InputFloat3("Input", pin.data, "%.00f");
						break;
					}
					case PinClass::Float4:
					{
						ImGui::InputFloat4("Input", pin.data, "%.00f");
						break;
					}
				}
			}

			ImNodes::EndOutputAttribute();
		}

	}


}

void Node::AddPin(PinType type,  PinClass classification, PinFlags flags)
{
	LOG_INFO("Adding Pin");

	Pin p = Pin();
	p.id = CreateAttributeID();
	p.type = type;
	p.classification = classification;
	
	switch (classification)
	{
	case PinClass::Float:
		p.data = (float*)malloc(sizeof(float));
		p.data[0] = 0;
		break;
	case PinClass::Float2:
		p.data = (float*)malloc(sizeof(float) * 2);
		p.data[0] = 0;
		p.data[1] = 0;
		break;
	case PinClass::Float3:
		p.data = (float*)malloc(sizeof(float) * 3);
		p.data[0] = 0;
		p.data[1] = 0;
		p.data[2] = 0;
		break;
	case PinClass::Float4:
		p.data = (float*)malloc(sizeof(float) * 4);
		p.data[0] = 0;
		p.data[1] = 0;
		p.data[2] = 0;
		p.data[3] = 0;
		break;
	default:
		break;
	}
	p.flags = flags;
	
	pins.push_back(p);
}




