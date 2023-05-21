#include "application.h"

#include "architecture/game.h"

iApplication::iApplication()
{
}

iApplication::~iApplication()
{
}

void iApplication::Load(iGame*game)
{
	this->game = game;
}
