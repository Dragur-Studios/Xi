#include "application.h"

#include "architecture/game.h"

iApplication::iApplication()
{
}

iApplication::~iApplication()
{
}

iGameApplication::iGameApplication()
{
}

iGameApplication::~iGameApplication()
{
}

void iGameApplication::Load(iGame* game)
{
	LOG_INFO("Game DLL Load Started!");

	this->game = game;

	LOG_SUCCESS("Game Loaded Successfully!");
}
