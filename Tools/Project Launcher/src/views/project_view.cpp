#include "project_view.h"

#include "GUI/stylesheet.h"

#include "GUI/XDocument/xdocument.h"

#include "GUI/Visual Elements/label.h"
#include "GUI/Visual Elements/Button.h"
#include "GUI/Visual Elements/TextField.h"
#include "GUI/visual elements/group.h"
#include "GUI/xss.h"


ProjectsView::ProjectsView() : View("Projects")
{
	_filepath = "views/styles/project_launcher.xss";
	Compile();
}

void ProjectsView::CreateProject() {
	LOG_SUCCESS("Button Pressed!");
}

void ProjectsView::OnCreateGUI()
{
	auto recompileXSSbutton = new Button("Recompile XSS", "recompile_btn", [&]() {
			Compile();
		});

	_document->Add(recompileXSSbutton);

	auto label = new Label("VVVVVVVVVVVVV Test Stuff VVVVVVVVVVVVVVVVVVV");
	
	_document->Add(label);

	auto btn_group = new Group();
	btn_group->_id = "buttons_group";

	for (int i = 0; i < 5; i++)
	{
		auto btn = new Button("Click Me", CreateProject);
		int id = i + 1;
		btn->_id = std::to_string(id);
		
		btn_group->Add(btn);
	}
	
	_document->Add(btn_group);

	auto textField = new TextField();
	
	_document->Add(textField);

}

ProjectsView::~ProjectsView()
{
}


void ProjectsView::HandleContextMenu()
{
}
