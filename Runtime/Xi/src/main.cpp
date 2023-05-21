
#include <iostream>
#include <Windows.h>

#include "architecture/application.h"
#include "architecture/project.h"
#include "debug/debug.h"


#include "project generation/attach.h"
#include "project generation/generate.h"

#define EDITOR 1
#define PLAYER 0

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define ENABLE_CRT_MEMORY_LEAK_DETECTION() \
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#else
#define ENABLE_CRT_MEMORY_LEAK_DETECTION() ((void)0)
#endif

int main() {
	// Enable CRT memory leak detection
	ENABLE_CRT_MEMORY_LEAK_DETECTION();

	std::string project_name;

	std::cout << "enter project name" << std::endl;
	std::getline(std::cin, project_name);

	ProjectGeneratorLocationInfo createInfo{ };
	createInfo.Drive = "Z:\\";
	createInfo.Filepath = "Xi\\Projects\\";
	createInfo.ProjectName = project_name;

	XiProject* project = ProjectGenerator::GenerateProject(&createInfo);

#if EDITOR
	ATTACH_EDITOR(project);
#elif PLAYER
	ATTACH_PLAYER(gameName);
#else

#endif
	
	return 0;
}

