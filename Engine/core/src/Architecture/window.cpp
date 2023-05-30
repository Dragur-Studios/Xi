#include "window.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>


Window::Window(const char* caption ) : caption{ caption } {
	

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// GLFW NEEDS to be Initilized PER THREAD
	glfwInit();

	win = glfwCreateWindow(600, 400, this->caption.c_str(), nullptr, nullptr);
	
	if (win == nullptr) {
		LOG_ERROR("WINDOW IS NULL!");
		return;
	}


	glfwMakeContextCurrent(win);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_ERROR("Failed to initialize GLAD");
	}


	glViewport(0, 0, 600, 400);

	IMGUI_CHECKVERSION();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	
	ImGui_ImplGlfw_InitForOpenGL(win, true);
	if (!ImGui_ImplOpenGL3_Init("#version 450")) {
		LOG_ERROR("ImGUi Could not Be Initilized!");
		return;
	}

	//glfwSetFramebufferSizeCallback(win, on_resize);


}

void Window::on_resize(struct GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}


bool Window::ProcessEvents() {

	bool exit = glfwWindowShouldClose(win);

	if (exit)
		return false;

	glfwPollEvents();

	// clear the GUI BUFFER
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (ImGui::Begin("Demo Window")) {
		ImGui::Button("Press Me");
		ImGui::End();
	}


	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	int size_w, size_h;
	glfwGetFramebufferSize(win, &size_w, &size_h);
	glViewport(0, 0, 600, 400);

	glfwSwapBuffers(win);


	
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

