#include "XiLauncher.h"

#include "architecture/window.h"
#include "architecture/game.h"

#include "views/project_view.h"

XiLauncher::XiLauncher()
{
}

XiLauncher::~XiLauncher()
{
}

void XiLauncher::OnInitilize()
{
	window = new Window("Xi Project Launcher");

	window->AddView(new ProjectsView());
	
}

void XiLauncher::OnTick()
{
	while (true) {
		if (!window->ProcessEvents())
			break;
	}
}

void XiLauncher::OnShutdown()
{
	delete window;
}



iApplication* CreateProjectLauncher()
{
	return new XiLauncher();
}


