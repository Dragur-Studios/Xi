#include "xdocument.h"

#include "gui/stylesheet.h"
#include "gui/Visual Elements/visual_element.h"
#include "gui/Visual Elements/group.h"
#include "gui/Visual Elements/label.h"
#include "gui/Visual Elements/button.h"
#include "gui/Visual Elements/textField.h"
#include "gui/xss.h"

#include "Util/tinyxml2.h"

tinyxml2::XMLDocument xml;

void ParseAttribute(XDocument* doc, VisualElement* element, const tinyxml2::XMLAttribute* attrib) {
	std::string name = attrib->Name();
	// to lower 
	transform(name.begin(), name.end(), name.begin(), ::tolower);

	if (name == "name") {
		element->_name = attrib->Value();
	}
	else if (name == "id") {
		element->_id = attrib->Value();
	}

}

void ParseElement(XDocument* doc, tinyxml2::XMLElement* element) {
	std::string _class = element->Name();
	// to lower 
	transform(_class.begin(), _class.end(), _class.begin(), ::tolower);
	
	VisualElement* pElement = nullptr;

	if (_class == "root") {
		pElement = new Group();
		pElement->_class = "root";
	}
	else if (_class == "group") {
		pElement = new Group();
	}
	else if (_class == "label") {
		pElement = new Label(element->GetText());
	}
	else if (_class == "button") {
		pElement = new Button(element->GetText());
	}
	else if (_class == "textfield") {
		pElement = new TextField();
	}

	if(pElement != nullptr)
		doc->Add(pElement);

	// process attributes
	const tinyxml2::XMLAttribute* pAttrib = element->FirstAttribute();
	while (pAttrib) {
		ParseAttribute(doc, pElement, pAttrib);
		pAttrib = pAttrib->Next();
	}

}

void TraverseXMLTree(XDocument* doc, tinyxml2::XMLElement* element, int depth = 0)
{
	for (int i = 0; i < depth; i++)
	{
		std::cout << "\t";
	}
	std::cout << "Element Name: " << element->Name() << std::endl;

	// the name must match certian criteria. 
	// known elements are the:
	// root, group, label, button, textField
	
	ParseElement(doc, element);
		
	

	tinyxml2::XMLElement* child = element->FirstChildElement();

	// continue onto children
	while (child) {
		TraverseXMLTree(doc, child, depth + 1);
		child = child->NextSiblingElement();
	}
}

XDocument::XDocument(const std::string& modelPath, const std::string& stylePath)
	: _filepath{modelPath}, _stylepath{stylePath}
{
	XssEngine::Compile(_stylepath);

	auto result = xml.LoadFile(modelPath.c_str());

	if (result != tinyxml2::XML_SUCCESS) {

		switch (result)
		{
		case tinyxml2::XML_NO_ATTRIBUTE:
			LOG_ERROR("XML File Error: No Attributes" + _filepath);
			break;
		case tinyxml2::XML_WRONG_ATTRIBUTE_TYPE:
			LOG_ERROR("XML File Error: No Attribute Type" + _filepath);
			break;
		case tinyxml2::XML_ERROR_FILE_NOT_FOUND:
			LOG_ERROR("XML File Error: File could not be found " + _filepath);
			break;
		case tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED:
			LOG_ERROR("XML File Error: File could not be opened " + _filepath);
			break;
		case tinyxml2::XML_ERROR_FILE_READ_ERROR:
			LOG_ERROR("XML File Error: File Read Error " + _filepath);
			break;
		case tinyxml2::XML_ERROR_PARSING_ELEMENT:
			LOG_ERROR("XML File Error: Elements Failed to Parse "  + _filepath);
			break;
		case tinyxml2::XML_ERROR_PARSING_ATTRIBUTE:
			LOG_ERROR("XML File Error: Attrubte Failed to Parse " + _filepath);
			break;
		case tinyxml2::XML_ERROR_PARSING_TEXT:
			LOG_ERROR("XML File Error: Text Failed to Parse " + _filepath);
			break;
		case tinyxml2::XML_ERROR_PARSING_CDATA:
			LOG_ERROR("XML File Error: CData Failed to Parse " + _filepath);
			break;
		case tinyxml2::XML_ERROR_PARSING_COMMENT:
			LOG_ERROR("XML File Error: Comment Failed to Parse " + _filepath);
			break;
		case tinyxml2::XML_ERROR_PARSING_DECLARATION:
			LOG_ERROR("XML File Error: Decleration Failed to Parse " + _filepath);
			break;
		case tinyxml2::XML_ERROR_PARSING_UNKNOWN:
			LOG_ERROR("XML File Error: Unknown Parsing Error " + _filepath);
			break;
		case tinyxml2::XML_ERROR_EMPTY_DOCUMENT:
			LOG_ERROR("XML File Error: Document is Empty!" + _filepath);
			break;
		case tinyxml2::XML_ERROR_MISMATCHED_ELEMENT:
			LOG_ERROR("XML File Error: Mismatched Element" + _filepath);
			break;
		case tinyxml2::XML_ERROR_PARSING:
			LOG_ERROR("XML File Error: Parsing Error " + _filepath);
			break;
		case tinyxml2::XML_CAN_NOT_CONVERT_TEXT:
			LOG_ERROR("XML File Error: Text Could not be converted! " + _filepath);
			break;
		case tinyxml2::XML_NO_TEXT_NODE:
			LOG_ERROR("XML File Error: No Text Node Expected on a node that requires text " + _filepath);
			break;
		case tinyxml2::XML_ELEMENT_DEPTH_EXCEEDED:
			LOG_ERROR("XML File Error: Element Depth limit exceded " + _filepath);
			break;
		case tinyxml2::XML_ERROR_COUNT:
			LOG_ERROR("XML File Error: Count error " + _filepath);
			break;
		default:
			break;
		}

		return;
	}

	auto xmlroot = xml.RootElement();
	TraverseXMLTree(this, xmlroot);

}

XDocument::~XDocument()
{
	if(_root != nullptr)
		delete _root;
}

void XDocument::Update()
{
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
	if (_root == nullptr) {
		_root = element;
		return;
	}

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

	ss << (std::string(depth * 2, ' ') + "<" + node->_class + (node->_children.empty() ? "/>" : ">") + "\n");

	if (node->_children.empty()) 
		return;
	
	for (auto& child : node->_children) {
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

void XDocument::Compile()
{
	//delete _root;

	XssEngine::Compile(_stylepath);
	
	auto result = xml.LoadFile(_filepath.c_str());
}

void XDocument::UpdateCursorPosition(VisualElement* node, ImVec2& cursorPos)
{
	auto styleSheet = XssEngine::GetStyleSheet(node);

	if (styleSheet == nullptr)
		return;

	auto width = (SingleValueProperty<float>*)styleSheet->properties["width"];
	auto height = (SingleValueProperty<float>*)styleSheet->properties["height"];
	auto padding = (MultiValueProperty<float, 4>*)styleSheet->properties["padding"];
	auto margin = (MultiValueProperty<float, 4>*)styleSheet->properties["margin"];
	auto border = (MultiValueProperty<float, 4>*)styleSheet->properties["border"];

	auto flex_direction = (SingleValueProperty<ImFlexDirection>*)styleSheet->properties["flex-direction"];

	if (flex_direction->value == ImFlexDirection::Row)
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

	if (node->_children.empty()) 
		return;
	
	for (auto& child : node->_children)
	{
		Render(child, cursorPos, depth + 1);
	}
}

void XDocument::PropagateEvents(VisualElement* node)
{
	if (node == nullptr)
		return;

	node->OnEvent();

	if (node->_children.empty() || node->_stop_propagation)
		return;

	for (const auto child : node->_children)
	{
		PropagateEvents(child);
	}
}



