#include "view.h"

#include "imgui/imgui.h"

View::View(const std::string& name)
	: show{ true }, name{ name }, windowFlags{ 0 }
{

}

View::~View()
{
}

void View::Draw() 
{
	if (show)
	{
		if (ImGui::Begin(name.c_str(), &show, (ImGuiWindowFlags)windowFlags)) {
			Update();
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
