#include "application.h"

#include "architecture/game.h"
#include "Architecture/window.h"

iApplication::iApplication()
{
}

iApplication::~iApplication()
{

}

iGameApplication::iGameApplication() 
	: game{nullptr}, window{nullptr}
{
}

iGameApplication::~iGameApplication()
{	
	delete window;
}

