#include "Editor.h"

#include "architecture/window.h"
#include "architecture/game.h"

#include "imgui/imgui.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include "views/Terminal.h"
#include "views/Inspector.h"
#include "GUI/graph_view.h"

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
	

	this->window->AddView(new Terminal());
	this->window->AddView(new Inspector());
	this->window->AddView(new GraphView("Nodes"));


}

void Editor::OnTick()
{

	static int tick_count = 0;
	static bool play = false;
	while (true) {

		if (!window->ProcessEvents())
			break;
		
		if (play) {

			if (tick_count == 0) {	
				game->OnInitilize(); // the game is just starting up. run all initilization code here
			}
		
			game->OnTick();	// all game logic updates.
			
			tick_count++;
		}
		else {

			if(tick_count != 0)		// the game was previously running it needs to be shut down
				game->OnShutdown();

			tick_count = 0;
		}

	}

}

void Editor::OnShutdown()
{

}



iApplication* CreateEditor()
{
	return new Editor();
}


