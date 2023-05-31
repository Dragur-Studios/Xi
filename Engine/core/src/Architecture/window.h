#pragma once

#include "pch.h"

class Window
{
public:
	Window(const char* caption);
	~Window();

	void SetCaption(const char* caption);
	bool ProcessEvents();

	void AddView(class View* v);
	void RemoveView(class View* v);

	static void on_resize(struct GLFWwindow* window, int width, int height);

protected:
	void SetStyle();

private:
	std::string caption;
	std::vector<class View*> views;
	struct GLFWwindow* win;

};

