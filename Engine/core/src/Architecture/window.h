#pragma once

#include "pch.h"

#include <mutex>
#include <condition_variable>
#include <atomic>

struct WindowThreadData {
	struct GLFWwindow* pWindow;
	std::condition_variable* condition;
};

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

	static void RenderThunk(WindowThreadData* threadData);

	static void on_resize(struct GLFWwindow* window, int width, int height);
	

protected:
	void SetStyle();

private:
	std::string caption;
	std::vector<class View*> views;
	struct GLFWwindow* win;
	int width;
	int height;


	std::condition_variable eventsCV;
	std::mutex drawGUIMutex;
	std::thread eventThread;

	WindowThreadData data{};

};

