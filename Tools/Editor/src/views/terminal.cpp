#include "terminal.h"

#include "imgui/imgui.h"

Terminal::Terminal()
	: View("Terminal", "", ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar), stdInterceptor{nullptr}
{
	stdInterceptor = new ImGuiStreamInterceptor(std::cout);

}

Terminal::~Terminal()
{
}

//void Terminal::Update()
//{
//	if (ImGui::Button("Clear")) {
//		stdInterceptor->ClearLogs();
//	}
//
//	auto region = ImGui::GetWindowContentRegionMax();
//	region.x -= 5;
//	region.y -= 50;
//
//	ImGui::BeginChild("###LOGS", region, true, ImGuiWindowFlags_::ImGuiWindowFlags_AlwaysVerticalScrollbar);
//
//	for (size_t i = 0; i < stdInterceptor->LogCount(); i++)
//	{
//
//		ImVec4 background(0.08f, 0.08f, 0.08f, 1.0f);
//		ImVec4 fontColor(1.0f, 1.0f, 1.0f, 1.0f);
//
//		if (i % 2 == 0) {
//
//			background.x *= 1.15f;
//			background.y *= 1.15f;
//			background.z *= 1.15f;
//			background.w = 1.0f;
//		}
//
//		ImVec2 contentRegionSize = ImGui::GetWindowContentRegionMax();
//		float lineHeight = ImGui::GetTextLineHeight() * 4.0f;
//		
//		auto start = ImGui::GetCursorScreenPos();
//		auto end = start;
//		end.x += contentRegionSize.x;
//		end.y += lineHeight;
//
//		ImGui::GetWindowDrawList()->AddRectFilled(start, end, ImGui::ColorConvertFloat4ToU32(background));
//			
//		
//		ImGui::TextColored(fontColor, "%s", stdInterceptor->GetLog(i).c_str());
//
//	
//		ImGui::Separator();
//
//		ImGui::SetScrollHereY();
//	}
//
//	ImGui::EndChild();
//
//}

//void Terminal::HandleContextMenu()
//{
//}
