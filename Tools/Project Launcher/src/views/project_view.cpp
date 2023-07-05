#include "project_view.h"

int ProjectsView::counter = 0;
ProjectsView::ProjectsView() : View("Projects", "views/projectsLauncher.xml")
{

	auto label = new Label("Hello World");
	Add(label);


	auto button = new Button("Click Me", CreateProject);
	
	button->styleSheet.color = ImGui::ColorConvertU32ToFloat4(0xFFFFEEFF);
	button->styleSheet.backgroundColor = ImGui::ColorConvertU32ToFloat4(0xFF161616);
	button->styleSheet.backgroundHoverColor = ImGui::ColorConvertU32ToFloat4(0xFF484848);
	button->styleSheet.padding = ImVec4(20, 20, 20, 20);
	button->styleSheet.margin = ImVec4(150, 5, 150, 5);
	button->styleSheet.border = ImVec4(5, 5, 5, 5);
	button->styleSheet.width = 250;
	button->styleSheet.height = 48;

	Add(button);

}

void ProjectsView::CreateProject() {
	LOG_SUCCESS("Button Pressed!");
}

ProjectsView::~ProjectsView()
{
}


void ProjectsView::HandleContextMenu()
{
}
