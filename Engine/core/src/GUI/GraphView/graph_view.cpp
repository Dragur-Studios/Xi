#include "graph_view.h"
#include <filesystem>

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

#include "graph_renderer.h"


#include "imnodes/imnodes.h"

#include "nodes.h"
#include "nodes/start_node.h"

std::map<std::string, NodeData> GraphView::searchResults{};
std::map<std::string, NodeData> GraphView::nodeTable=
{
	{ "Add",		NodeData{ "math",	NodeType::Add}},
	{ "Subtract",	NodeData{ "math",	NodeType::Subtract }},
	{ "Multiply",	NodeData{ "math",	NodeType::Multiply} },
	{ "Divide",		NodeData{ "math",	NodeType::Divide }},
	{ "Float",		NodeData{ "types",	NodeType::Float }},
	{ "Float2",		NodeData{ "types",	NodeType::Float2 }},
	{ "Float3",		NodeData{ "types",	NodeType::Float3 }},
	{ "Float4",		NodeData{ "types",	NodeType::Float4 }},
};

GraphView::GraphView(const std::string& name) 
	: View(name, "")
{
	renderer = new GraphRenderer();

	renderer->AddNode<StartNode>(0, 0);
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
	if (ImGui::IsMouseReleased(ImGuiMouseButton_::ImGuiMouseButton_Right) || (ImGui::IsKeyReleased(ImGuiKey_::ImGuiKey_Space) && ImGui::IsKeyDown(ImGuiKey_::ImGuiKey_LeftCtrl)) )
	{
		ImGui::OpenPopup("Context Menu");

		LOG_INFO("Opening Context Menu!");
	}
	if (ImGui::BeginPopupContextItem("Context Menu")) {

		auto mp = ImGui::GetIO().MousePos;

		char buffer[256]{'\0'};

		ImGui::InputTextWithHint("###SEARCH_BAR", "Search", buffer, (size_t)sizeof(buffer), ImGuiInputTextFlags_CallbackCharFilter | ImGuiInputTextFlags_CallbackAlways, SearchAndFilter, this);

		searchQuery = std::string(buffer);

		if (!searchQuery.empty()) {
			ImGui::SameLine(); 
			
			if (ImGui::Button("Clear")) {
				searchQuery.clear();
			}
			
			for (const auto& kvp : searchResults)
			{
				auto name = kvp.first;
				auto data = kvp.second;

				if (ImGui::MenuItem(name.c_str())) {
					CreateNode(name, data.type, mp);
				}

			}
		
		}
		else {
			int idx = 0;
			for (const auto& kvp : nodeTable)
			{
				
				auto name = kvp.first;
				auto data = kvp.second;

				bool group = !data.group.empty();
				if (group) {
					bool group_open = ImGui::BeginMenu(data.group.c_str());
					if (group_open) {

						if (ImGui::MenuItem(name.c_str())) {
							CreateNode(name, data.type, mp);
						}
					
						ImGui::EndMenu();
					}

				}
				else {
					
					if (ImGui::MenuItem(name.c_str())) {
						CreateNode(name, data.type, mp);
					}
				}
				
				
				idx++;
			}

		
		}
		ImGui::EndPopup();
	}

}

void GraphView::CreateNode(const std::string& name, NodeType type, ImVec2 position)
{
		switch (type)
		{
		case NodeType::Float:
			renderer->AddNode<FloatNode>(position.x, position.y);
			break;
		case NodeType::Float2:
			renderer->AddNode<Float2Node>(position.x, position.y);
			break;
		case NodeType::Float3:
			renderer->AddNode<Float3Node>(position.x, position.y);
			break;
		case NodeType::Float4:
			renderer->AddNode<Float4Node>(position.x, position.y);
			break;


		case NodeType::Add:
			renderer->AddNode<AddNode>(position.x, position.y);
			break;
		case NodeType::Subtract:
			renderer->AddNode<SubtractNode>(position.x, position.y);
			break;
		case NodeType::Multiply:
			renderer->AddNode<MultiplyNode>(position.x, position.y);
			break;
		case NodeType::Divide:
			renderer->AddNode<DivideNode>(position.x, position.y);
			break;
		}
}

int GraphView::SearchAndFilter(ImGuiInputTextCallbackData* data)
{
	auto gView =static_cast<GraphView*>(data->UserData);

	// aquire a unmodifiable copy of the query, it should be presented to the search engine as
	// a cas-in-sensative search using lower_case
	std::string query = std::string(gView->searchQuery);
	
	std::transform(query.begin(), query.end(), query.begin(), ::tolower);	// case insensitive check

	// look throuh the index
	for (const auto& kvp : nodeTable)
	{
		// aquire the current name to check against
		auto name = kvp.first;												// ensure cases match				
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);	// case insensitive check

		// if the name matches exactly then emplace the result.
		if (name.compare(query) == 0) {
			searchResults.emplace(kvp);
			break;
		}
		// if the name doesnt match at all. and the filter has added it to the results
		// it needs to be removed. remove it
		else if (name.compare(query) != 0) {
			if (searchResults.find(kvp.first) != searchResults.end()) {
				searchResults.erase(kvp.first);
			}
		}

		// display any items that currently contain what is found in the search filter.
		if (name.find(query) != std::string::npos)
		{
			searchResults.emplace(kvp);
		}
	}
	return 0;
}



