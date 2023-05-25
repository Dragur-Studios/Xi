//#pragma once

#include "architecture/application.h"
#include "Debug/debug.h"

class XiLauncher : public iApplication {
public:
	XiLauncher();
	~XiLauncher();

	virtual void OnInitilize() override;

	virtual void OnTick() override;

	virtual void OnShutdown() override;

	class Window* window;
};

extern "C" _declspec(dllexport) iApplication* CreateProjectLauncher();

