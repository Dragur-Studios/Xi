#pragma once

#include "pch.h"

class Window
{
public:
	Window(const char* caption);
	~Window();

	void SetCaption(const char* caption);
	bool ProcessEvents();

	struct GLFWwindow* win;

private:
	std::string caption;

};

