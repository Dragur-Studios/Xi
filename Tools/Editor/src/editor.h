//#pragma once

#include "architecture/application.h"
#include "Debug/debug.h"

class Editor : public iGameApplication {
public:
	Editor();
	~Editor();

	virtual void OnInitilize(class iGame* igame) override;

	virtual void OnTick() override;

	virtual void OnShutdown() override;

};

extern "C" _declspec(dllexport) iApplication* CreateEditor();

