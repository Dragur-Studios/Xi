//#pragma once

#include "architecture/application.h"
#include "Debug/debug.h"

class Editor : public iApplication {
public:
	Editor();
	~Editor();

	virtual void OnInitilize() override;

	virtual void OnTick() override;

	virtual void OnShutdown() override;

	class Window* window;
};

extern "C" _declspec(dllexport) iApplication* CreateEditor();

