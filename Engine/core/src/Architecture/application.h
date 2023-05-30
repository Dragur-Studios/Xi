#pragma once


#ifdef _WIN32
#include <windows.h>
#endif

class iApplication
{
public:
	iApplication();
	virtual ~iApplication();

	virtual void OnInitilize() {};
	virtual void OnTick() = 0;
	virtual void OnShutdown() {};
};

class iGameApplication : public iApplication
{
public:
	iGameApplication();
	virtual ~iGameApplication();

	virtual void OnInitilize(class iGame* igame) = 0;

	class iGame* game;
	class Window* window;
};

typedef iApplication* (*XiApplicationFunc)();
typedef iGameApplication* (*XiGameApplicationFunc)();