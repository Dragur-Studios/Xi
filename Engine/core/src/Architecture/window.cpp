#include "window.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

#include "GUI/view.h"

#include <algorithm>
#include "IO/FileSystem.h"
#include <string>
#include <sstream>

void showDockSpace(bool* p_open)
{
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("###DockSpace", p_open, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	// DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	ImGui::End();
}


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

	// set up docking and navigation
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;



	SetStyle();
	

	ImGui_ImplGlfw_InitForOpenGL(win, true);
	if (!ImGui_ImplOpenGL3_Init("#version 450")) {
		LOG_ERROR("ImGUi Could not Be Initilized!");
		return;
	}

	glfwSetFramebufferSizeCallback(win, on_resize);


}


void Window::on_resize(struct GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Window::SetStyle()
{
	std::string location = "D:\\Dev\\ImGUI\\Styles\\";
	std::string filename = "Style.txt";
	std::string contentBuffer;

	bool styleExists = FileSystem::File::Read(location + filename, contentBuffer);
	
	ImVec4* colors = ImGui::GetStyle().Colors;

	if (styleExists)
	{
		LOG_INFO("Reading Styles!\n\n\n");

		std::istringstream iss(contentBuffer);
		std::string line;
		int c = 0;
		while (std::getline(iss, line)) 
		{
			std::istringstream lss(line);
			
			float r, g, b, a;
			char comma;

			lss >> r >> comma >> g >> comma >> b >> comma >> a;
		
			colors[c] = ImVec4(r, g, b, a);

			c++;
		}

	}
	else {

		LOG_INFO("Creating Styles!\n\n\n");

		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.94f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.54f, 0.54f, 0.54f, 0.67f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.91f, 0.26f, 0.98f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.91f, 0.26f, 0.98f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.91f, 0.26f, 0.98f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.57f, 0.57f, 0.57f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.1f, 0.1f, 0.1f, 0.94f);
		colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_Tab] = ImVec4(0.1f, 0.1f, 0.1f, 0.94f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.1f, 0.1f, 0.1f, 0.97f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);
		colors[ImGuiCol_DockingPreview] = ImVec4(0.91f, 0.26f, 0.98f, 0.70f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.22f, 0.81f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

		for (size_t i = 0; i < ImGuiCol_::ImGuiCol_COUNT; i++)
		{
			auto r = std::to_string(colors[i].x);
			auto g = std::to_string(colors[i].y);
			auto b = std::to_string(colors[i].z);
			auto a = std::to_string(colors[i].w);

			contentBuffer += r + ", " + g + ", " + b + ", " + a + '\n';
		}
		contentBuffer += "\0";

		FileSystem::File::Create(location, filename);
		FileSystem::File::Update(location + filename, contentBuffer);
	}

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
	

	bool show = true;
	showDockSpace(&show);

	for (const auto v : views) {
		v->Draw();
	}
	auto style = ImGui::GetStyle();
	ImGui::ShowStyleEditor(&style);

	ImGui::Render();

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	int size_w, size_h;
	glfwGetFramebufferSize(win, &size_w, &size_h);
	glViewport(0, 0, 600, 400);

	glfwSwapBuffers(win);




	
	return true;
}

void Window::AddView(View* v)
{
	views.push_back(v);
}

void Window::RemoveView(View* v)
{
	auto remove = std::find(begin(views), end(views), v);
	if (remove != end(views)) {
		auto iterator = std::remove(begin(views), end(views), v);
		views.erase(iterator, views.end());
	}
}

void Window::SetCaption(const char* caption) {
	this->caption = std::string(caption);
	glfwSetWindowTitle(win, this->caption.c_str());
}

Window::~Window() {

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(win);
	glfwTerminate();
}

