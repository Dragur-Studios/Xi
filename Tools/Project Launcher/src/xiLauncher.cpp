#include "XiLauncher.h"

#include "architecture/window.h"
#include "architecture/game.h"

XiLauncher::XiLauncher()
{
}

XiLauncher::~XiLauncher()
{
}

void XiLauncher::OnInitilize()
{
	window = new Window("Xi Project Launcher");
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


