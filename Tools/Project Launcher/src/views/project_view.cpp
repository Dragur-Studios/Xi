#include "project_view.h"

#include "GUI/stylesheet.h"
#include "GUI/Visual Elements/label.h"
#include "GUI/Visual Elements/Button.h"


int ProjectsView::counter = 0;

ProjectsView::ProjectsView() : View("Projects", "views/projectsLauncher.xml")
{




}



void ProjectsView::CreateProject() {
	LOG_SUCCESS("Button Pressed!");
}

void ProjectsView::OnCreateGUI()
{
	auto label = new Label("Hello World");
	label->styleSheet = styleMap["_label"];
	Add(label);


	auto btn = new Button("Click Me", CreateProject);
	btn->styleSheet = styleMap["_button"];
	Add(btn);

}

ProjectsView::~ProjectsView()
{
}


void ProjectsView::HandleContextMenu()
{
}
