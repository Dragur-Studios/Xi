#include "view.h"

#include "imgui/imgui.h"
#include "Visual Elements/visual_element.h"

#include "Util/tinyxml2.h"

tinyxml2::XMLDocument xmlDocument;

View::View(const std::string& name)
	: show{ true }, name{ name }, windowFlags{ 0 }
{

}

View::~View()
{
}

void View::Render()
{
	RenderVisualElement(root); 
}
void View::Draw() 
{
	if (root == nullptr)
		return;

	if (show)
	{
		if (!ImGui::Begin(name.c_str(), &show, (ImGuiWindowFlags)windowFlags)) {
			ImGui::End();
		}
		else {
			Update();
			Render();
			ImGui::End();
		}
	}
}

void View::Show()
{
	show = true;
}

void View::Hide()
{
	show = false;
}

void View::RenderVisualElement(VisualElement* node)
{
	if (node == nullptr)
		return;

	ImGui::SetCursorPos(node->position);
	ImGui::SetNextWindowPos(node->size);
	ImGui::Begin(node->guid.c_str());
		
	ImGui::End();
	
	for (auto& child : node->children)
	{
		RenderVisualElement(child);
	}
}
