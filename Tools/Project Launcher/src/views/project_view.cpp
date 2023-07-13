#include "project_view.h"

#include "GUI/XDocument/xdocument.h"
#include "GUI/Visual Elements/button.h"

ProjectsView::ProjectsView() 
	: View("Projects","views/project_launcher.xxml", "views/styles/project_launcher.xss")
{

}

void ProjectsView::OnCreateGUI()
{
	//LOG_INFO("On Create GUI");
	auto btn = (Button*)_document->Q<Button>("recompile_button");
	if (btn != nullptr) {
		btn->clicked += [&]() {
			Compile();
			LOG_INFO("RECOMPILE");
		};
	}
}

void ProjectsView::OnGUI()
{
	//LOG_INFO("OnGUI");

	
}

ProjectsView::~ProjectsView()
{
}


void ProjectsView::HandleContextMenu()
{
}
