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

void iGameApplication::Load(iGame*game)
{
	this->game = game;
}
