#pragma once

#include "pch.h"

#include <mutex>
#include <condition_variable>
#include <atomic>

class Window
{
public:
	Window(const char* caption);
	~Window();

	void SetCaption(const char* caption);
	bool ProcessEvents();

	void Resize(int width, int height);

	void AddView(class View* v);
	void RemoveView(class View* v);

	void DrawFrame();

	static void on_resize(struct GLFWwindow* window, int width, int height);
	

protected:
	void SetStyle();

private:
	std::string caption;
	std::vector<class View*> views;
	struct GLFWwindow* win;
	int width;
	int height;

};

