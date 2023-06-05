#include "graph_view.h"
#include <filesystem>

#include "imgui/imgui.h"

void GraphView::HandleZoom()
{
	ImGuiIO& io = ImGui::GetIO();

	// Check if the mouse wheel changed
	if (io.MouseWheel != 0)
	{
		// Adjust the zoom level based on the mouse wheel delta
		float zoomDelta = 0.1f;

		auto zoom = renderer.GetZoom();

		zoom -= io.MouseWheel * zoomDelta;
		// Clamp the zoom level to a desired range

		float minZoom = 0.1f;	// / 0.1f 
		float maxZoom = 15.0f;	// / 15.0f

		zoom = std::clamp(zoom, minZoom, maxZoom);

		renderer.UpdateZoom(zoom);

	}
}




GraphView::GraphView(const std::string& name) 
	: View(name)
{
};


void GraphView::Update()
{
	auto cameraPosition = renderer.GetOriginOffset();

	static std::chrono::high_resolution_clock::time_point last_time = std::chrono::high_resolution_clock::now();
	const auto current_time = std::chrono::high_resolution_clock::now();
	
	float deltaTime = 0;

	if (last_time != current_time) {

		deltaTime = std::chrono::duration<float, std::milli>(current_time - last_time).count() / 1000.0f;
		LOG_INFO("DeltaTime: " + std::to_string(deltaTime));

		last_time = std::chrono::high_resolution_clock::now();
	}

	//ImGui::SetCursorPos(ImVec2(10, 50));
	//ImGui::Text("position: (%s)", (std::to_string(cameraPosition.x) + ", " + std::to_string(cameraPosition.y)).c_str());

	//auto mp = to_glm_vec(ImGui::GetMousePos());
	//auto mp_world = renderer.ScreenToWorldPosition(mp);

	//ImGui::SetCursorPos(ImVec2(10, 70));
	//ImGui::Text("mouse position(screen): (%s)", (std::to_string(mp.x) + ", " + std::to_string(mp.y)).c_str());

	//ImGui::SetCursorPos(ImVec2(10, 90));
	//ImGui::Text("mouse position(world): (%s)", (std::to_string(mp_world.x) + ", " + std::to_string(mp_world.y)).c_str());


	if (ImGui::IsWindowFocused()) {
		if (ImGui::IsMouseDragging(ImGuiMouseButton_Middle)) 
		{
			cameraPosition -= to_glm_vec(ImGui::GetIO().MouseDelta) * deltaTime;
			renderer.UpdateScreenOffset(cameraPosition);
		}
	}


	renderer.Update();

	HandleZoom();
	HandleContextMenu();

}

void GraphView::Render()
{	
	renderer.Render();
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

			AddNode("New Node", to_glm_vec(ImGui::GetMousePos()), vec2(100.0f, 50.0f));
		}

		ImGui::EndPopup();
	}

}

void GraphView::AddNode(std::string label, vec2 position, vec2 size)
{
	Node* newNode = new Node();
	newNode->label = label;

	glm::mat4x4 model(1.0f);
	newNode->matrix = model;
	newNode->matrix[0][0] = size.x;
	newNode->matrix[1][1] = size.y;
	newNode->matrix[3][0] = position.x;
	newNode->matrix[3][1] = position.y;

	//nodes.push_back(newNode);

	renderer.AddNode(newNode);

}

void GraphView::ConnectNodes(Node* a, Node* b)
{
	renderer.AddConnection(a, b);
}
