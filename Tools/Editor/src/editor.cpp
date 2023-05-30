#include "Editor.h"

#include "architecture/window.h"
#include "architecture/game.h"

#include "imgui/imgui.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

Editor::Editor()
{
	
}

Editor::~Editor()
{
}

void Editor::OnInitilize(iGame* igame)
{
	this->game = igame;

	if (game == nullptr)
	{
		LOG_ERROR("Game is Null");
		return;
	}

	this->window = new Window(game->GetName().c_str());
	
	if (window == nullptr) {
		LOG_ERROR("Window is Null.");
		return;
	}
	
	// temporary DOES NOT STAY!!
	game->OnInitilize();
}

void Editor::OnTick()
{
	while (true) {

		if (!window->ProcessEvents())
			break;
		
		game->OnTick();

	}
	
	game->OnShutdown();
}

void Editor::OnShutdown()
{

}



iApplication* CreateEditor()
{
	return new Editor();
}


