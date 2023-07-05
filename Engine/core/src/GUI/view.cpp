#include "view.h"

#include "imgui/imgui.h"
#include "Visual Elements/visual_element.h"

#include "Util/tinyxml2.h"



View::View(const std::string& name, const std::string& filepath, int flags)
	: _show{ true }, _name{ name }, _windowFlags{ flags }, _filepath{filepath}, _root{new Group()}
{ }

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
			Render(_root);
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

void View::Render(VisualElement* node)
{
	if (node == nullptr)
		return;

	//ImGui::BeginChild(node->_guid.c_str());
	
	node->Draw();

	for (auto& child : node->children)
	{
		Render(child);
	}

	//ImGui::EndChild();
}
