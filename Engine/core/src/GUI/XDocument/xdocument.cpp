#include "xdocument.h"

#include "gui/stylesheet.h"
#include "gui/Visual Elements/visual_element.h"
#include "gui/Visual Elements/group.h"
#include "gui/xss.h"

XDocument::XDocument()
{
	_root = new Group();
}

XDocument::~XDocument()
{
	if(_root != nullptr)
		delete _root;
}

void XDocument::Update()
{
	//if (_compile) {
	//	XssEngine::Compile(_filepath, ImGui::GetContentRegionMax());
	//	_compile = false;
	//}

	PropagateEvents(_root);
}

void XDocument::Draw()
{
	if (_root == nullptr) {
		LOG_WARNING("root element is null XDocument cannot render");
		return;
	}

	auto cursorPos = ImVec2(ImGui::GetCursorScreenPos());

	Render(_root, cursorPos);

}

void XDocument::Add(VisualElement* element)
{
	_root->Add(element);
}

void XDocument::Remove(VisualElement* element)
{
	_root->Remove(element);
}

void BuildStringTree(VisualElement* node, std::stringstream& ss, int depth = 0) {
	
	if (node == nullptr)
		return;

	if (depth > 10) // depth limit
		return;

	ss << (std::string(depth * 2, ' ') + "<" + node->_class + (node->children.empty() ? "/>" : ">") + "\n");

	if (node->children.empty()) 
		return;
	
	for (auto& child : node->children) {
		BuildStringTree(node, ss, depth + 1);
	}
	
	ss << (std::string(depth * 2, ' ') + "<" + node->_class + "/>" + "\n");
}

const std::string& XDocument::to_string()
{
	std::stringstream treeStream;
	BuildStringTree(_root, treeStream);
	auto str = treeStream.str();
	treeStream.clear();
	return str;
}

void XDocument::UpdateCursorPosition(VisualElement* node, ImVec2& cursorPos)
{
	if (node->_class == "root")
		return;

	auto styleSheet = XssEngine::GetStyleSheet(node);

	if (styleSheet == nullptr)
		return;

	auto width = (SingleValueProperty<float>*)styleSheet->properties["width"];
	auto height = (SingleValueProperty<float>*)styleSheet->properties["height"];
	auto padding = (MultiValueProperty<float, 4>*)styleSheet->properties["padding"];
	auto margin = (MultiValueProperty<float, 4>*)styleSheet->properties["margin"];
	auto border = (MultiValueProperty<float, 4>*)styleSheet->properties["border"];

	auto flex_direction = (SingleValueProperty<FlexDirection>*)styleSheet->properties["flex-direction"];

	if (flex_direction->value == FlexDirection::Row)
		cursorPos.x += width->value + padding->value[0] + margin->value[0] + border->value[0];
	else
		cursorPos.y += height->value + padding->value[1] + margin->value[1] + border->value[1];
	
}

void XDocument::DrawNode(VisualElement* node, ImVec2& cursorPos)
{
	ImDrawList* drawList = ImGui::GetWindowDrawList();

	// class is least likely
	auto styleSheet = XssEngine::GetStyleSheet(node);

	if (styleSheet == nullptr)
		return;

	//offset startposition by the padding, the margin, and the border sizes
	auto widthProp = (SingleValueProperty<float>*) styleSheet->properties["width"];
	auto heightProp = (SingleValueProperty<float>*) styleSheet->properties["height"];
	auto roundingProp = (SingleValueProperty<float>*) styleSheet->properties["rounding"];

	auto marginProp = (MultiValueProperty<float, 4>*) styleSheet->properties["margin"];
	auto borderProp = (MultiValueProperty<float, 4>*) styleSheet->properties["border"];
	auto paddingProp = (MultiValueProperty<float, 4>*) styleSheet->properties["padding"];
	auto shadowProp = (MultiValueProperty<float, 4>*) styleSheet->properties["shadow"];

	auto width = widthProp->value;
	auto height = heightProp->value;
	auto rounding = roundingProp->value;

	auto margin = marginProp->value;
	auto border = borderProp->value;
	auto padding = paddingProp->value;
	auto shadow = shadowProp->value;

	auto displaySize = ImGui::GetIO().DisplaySize;

	auto background_color = (SingleValueProperty<ImColorState>*) styleSheet->properties["background-color"];
	auto font_color = (SingleValueProperty<ImColorState>*) styleSheet->properties["font-color"];
	auto border_color = (SingleValueProperty<ImColorState>*) styleSheet->properties["border-color"];

	ImColor _background =
		node->_hover ?
		background_color->value.hover :
		node->_active ?
		background_color->value.active :
		background_color->value.normal;

	ImColor _font = node->_hover ?
		font_color->value.hover :
		node->_active ?
		font_color->value.active :
		font_color->value.normal;

	ImColor _border =
		node->_hover ?
		border_color->value.hover :
		node->_active ?
		border_color->value.active :
		border_color->value.normal;


	// draw shadow area
	{
		ImVec2 start = cursorPos;
		start.x += margin[0] / 2.0f;
		start.y += margin[1] / 2.0f;

		ImVec2 end = start;
		end.x += shadow[0] + border[0] + padding[0] + width;
		end.y += shadow[1] + padding[1] + height;

		drawList->AddRectFilled(start, end, _border, rounding);
	}

	//draw content area
	{
		ImVec2 start = cursorPos;
		start.x += (margin[0] / 2.0f) + (border[0] / 2.0f);
		start.y += (margin[1] / 2.0f) + (border[1] / 2.0f);

		ImVec2 end = start;
		end.x += padding[0] + width;
		end.y += padding[1] + height;

		node->_bounds = { start, end };
		
		node->OnCreateGUI();
	}

	// draw border area
	{
		ImVec2 start = cursorPos;
		start.x += margin[0] / 2.0f;
		start.y += margin[1] / 2.0f;

		ImVec2 end = start;
		end.x += border[0] + padding[0] + width;
		end.y += border[1] + padding[1] + height;

		drawList->AddRect(start, end, _border, rounding, 0, border[0]);
	}

}

void XDocument::Render(VisualElement* node, ImVec2& cursorPos, int depth)
{
	if (node == nullptr) 
		return;
	
	DrawNode(node, cursorPos);	
	UpdateCursorPosition(node, cursorPos);

	if (node->children.empty()) 
		return;
	
	for (auto& child : node->children)
	{
		Render(child, cursorPos, depth + 1);
	}
}

void XDocument::PropagateEvents(VisualElement* node)
{
	if (node == nullptr)
		return;

	node->OnEvent();

	if (node->children.empty() || node->_stop_propagation)
		return;

	for (const auto child : node->children)
	{
		PropagateEvents(child);
	}
}

