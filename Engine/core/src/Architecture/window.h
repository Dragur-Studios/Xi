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
	
	static void on_resize(struct GLFWwindow* window, int width, int height);

private:
	std::string caption;

};

