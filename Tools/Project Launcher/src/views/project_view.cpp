#include "project_view.h"

ProjectsView::ProjectsView() : View("Projects", "views/projectsLauncher.xml")
{
	
	Add(new Button("Click Me", []() {
		}));


	Add(new Label("Hello World"));
}

ProjectsView::~ProjectsView()
{
}


void ProjectsView::HandleContextMenu()
{
}
