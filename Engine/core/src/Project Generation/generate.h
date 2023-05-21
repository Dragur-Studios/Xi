#pragma once

#include "pch.h"
#include "defs.h"


struct ProjectGeneratorLocationInfo {
	std::string Drive = "C:\\";
	std::string Filepath = "Xi\\Projects\\";
	std::string ProjectName = "New Project";
};


class ProjectGenerator {
public:
	static class XiProject* GenerateProject(ProjectGeneratorLocationInfo* plocationInfo);

protected:
	static void SetGenerationLocation(ProjectGeneratorLocationInfo* plocationInfo);
	static void InitilizeProjectFileStructure();
	
	// LUA FILE GENERATION
	static void CreateControlFile();
	// XiProject File Generation
	static void CreateProjectFile();

	static void CreateVisualStudioBuildFile();
	static void BuildVisualStudioSolution();

	static void CreateSourceFiles();
	static void BuildVisualStudioProject(const std::string& filepath);


private:
	static const std::string token_project;
	static const std::string token_workspace;
	static const std::string default_drive;
	static const std::string default_directory;
	static const std::string default_projectName;

	static std::string drive;
	static std::string directory;
	static std::string projectName;
};