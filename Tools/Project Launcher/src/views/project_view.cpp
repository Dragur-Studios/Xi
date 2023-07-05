#include "project_view.h"

int ProjectsView::counter = 0;
ProjectsView::ProjectsView() : View("Projects", "views/projectsLauncher.xml")
{

	auto label = new Label("Hello World");
	Add(label);


	auto button = new Button("Click Me", CreateProject);
	
	button->styleSheet.font_color.normal = 0xFFFFEEFF;
	button->styleSheet.font_color.hover = 0xFFFFEEFF;

	button->styleSheet.background_color.normal = 0xFF161616;
	button->styleSheet.background_color.hover = 0xFF484848;

	button->styleSheet.border_color.normal = 0xFF000000;
	button->styleSheet.border_color.hover = 0xFF161616;

	button->styleSheet.padding = { 20, 20, 20, 20 };
	button->styleSheet.margin = { 150, 5, 150, 5 };
	button->styleSheet.border = { 0.1f, 0.1f, 0.1f, 0.1f};
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
