#include "graph_view.h"
#include <filesystem>

#include "imgui/imgui.h"


#include "graph_renderer.h"

#include "imnodes/imnodes.h"


GraphView::GraphView(const std::string& name) 
	: View(name)
{
	renderer = new GraphRenderer();

};


void GraphView::Update()
{
	
	renderer->Update();

	HandleContextMenu();

}

void GraphView::Render()
{	
	renderer->Render();
}

void GraphView::HandleContextMenu()
{
	if (ImGui::IsMouseReleased(ImGuiMouseButton_::ImGuiMouseButton_Right)) 
	{
		ImGui::OpenPopup("Context Menu");

		LOG_INFO("Opening Context Menu!");
	}

	if (ImGui::BeginPopupContextItem("Context Menu")) {

		if (ImGui::MenuItem("New Node")) {
			//auto worldPosition = renderer.ScreenToWorldPosition();

			auto mp = ImGui::GetMousePos();

		
			//AddNode("New Node", to_glm_vec(ImGui::GetMousePos()), vec2(100.0f, 50.0f));

			renderer->AddNode(mp.x, mp.y);
		}

		ImGui::EndPopup();
	}

}



