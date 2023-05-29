#include "Editor.h"

#include "architecture/window.h"
#include "architecture/game.h"

Editor::Editor()
{
}

Editor::~Editor()
{
}

void Editor::OnInitilize()
{
	if (game == nullptr)
	{
		LOG_ERROR("Game is Null");
		return;
	}

	window = new Window(game->GetName().c_str());
}

void Editor::OnTick()
{
	while (true) {
		if (!window->ProcessEvents())
			break;
	}
}

void Editor::OnShutdown()
{
	delete window;
}



iApplication* CreateEditor()
{
	return new Editor();
}


