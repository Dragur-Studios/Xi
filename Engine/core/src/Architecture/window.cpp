#include "window.h"

#include "GLFW/glfw3.h"


Window::Window(const char* caption ) : caption{ caption } {
	
	// GLFW NEEDS to be Initilized PER THREAD
	glfwInit();

	win = glfwCreateWindow(600, 400, this->caption.c_str(), nullptr, nullptr);
	
	if (win == nullptr)
		return;

	glfwShowWindow(win);
}

bool Window::ProcessEvents() {

	bool exit = glfwWindowShouldClose(win);

	if (exit)
		return false;

	glfwPollEvents();

	return true;
}

void Window::SetCaption(const char* caption) {
	this->caption = std::string(caption);
	glfwSetWindowTitle(win, this->caption.c_str());
}

Window::~Window() {
	glfwDestroyWindow(win);
	glfwTerminate();
}

