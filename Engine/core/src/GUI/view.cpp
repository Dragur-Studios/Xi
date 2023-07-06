#include "view.h"

#include "imgui/imgui.h"
#include "GUI/stylesheet.h"
#include "Visual Elements/visual_element.h"
#include "Visual Elements/group.h"

#include "xss.h"

View::View(const std::string& name, const std::string& filepath, int flags)
	: _show{ true }, _name{ name }, _windowFlags{ flags }, _filepath{filepath}, _root{new Group()}
{ 
	
	// load filecontents from filepath.

	std::string _root_xss =
		"_root {\n"
		"background-color: 255, 255, 255, 255;\n"
		"width: 100;\n"
		"height: 30;\n"
		"color: 255, 255, 255, 255;\n"
		"}\n";

	std::string _label_xss =
		"_label {\n"
		"background-color: 255, 255, 255, 255;\n"
		"width: 100;\n"
		"height: 30;\n"
		"color: 255, 255, 255, 255;\n"
		"}\n";

	std::string _button_xss =
		"_button {\n"
		"background-color: 16, 16, 16, 255;\n"
		"width: 100;\n"
		"height: 30;\n"
		//"color: 255, 255, 255, 255;\n"
		"}\n";

	std::string test_xss =  _button_xss + _label_xss;

	ParseSelectorBlocks(test_xss, styleMap);


}

View::~View()
{
	delete _root;
}

void View::Add(VisualElement* element) {
	_root->Add(element);
}

void View::Remove(VisualElement* element) {
	_root->Remove(element);
}

void View::Draw() 
{
	if (_root == nullptr) {
		return;
	}

	if (_show)
	{
		if (!ImGui::Begin(_name.c_str(), &_show, (ImGuiWindowFlags)_windowFlags)) {
			ImGui::End();
		}
		else {
			auto cursorPos = ImVec2(ImGui::GetCursorScreenPos());
			Render(_root, cursorPos);

			ImGui::End();
		}
	}
}

void View::Show()
{
	_show = true;
}

void View::Hide()
{
	_show = false;
}

void View::RenderChild(VisualElement* node, ImVec2& cursorPos) {
	node->Draw(cursorPos);
	cursorPos.y += node->styleSheet->height + node->styleSheet->padding.y + node->styleSheet->margin.y + node->styleSheet->border.y;
}

void View::Render(VisualElement* node, ImVec2& cursorPos)
{
	if (node == nullptr)
		return;

	node->Draw(cursorPos);	// draws root <should be a group>

	for (auto& child : node->children)
	{
		RenderChild(child, cursorPos);
	}

}
