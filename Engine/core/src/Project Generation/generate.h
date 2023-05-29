#pragma once

#include "pch.h"
#include "defs.h"


struct ProjectGeneratorLocationInfo {
	std::string Drive = "C:\\"; 
	std::string Filepath = "Xi\\Projects\\";
	std::string WorkspaceDirectory = "New Workspace";
	
	// -- non nullables
	std::string ProjectName = "";
	enum class XiProjectType Type;
};


#define project_root(proj) proj->drive + proj->filepath + proj->workspace + proj->name + "\\"
#define workspace_root(proj) proj->drive + proj->filepath + proj->workspace


class ProjectGenerator {
public:
	static void GenerateProject(ProjectGeneratorLocationInfo* plocationInfo);

protected:
	static struct XiProject* CreateXiWorkspace(ProjectGeneratorLocationInfo* plocationInfo);
	static struct XiProject* CreateXiProject(ProjectGeneratorLocationInfo* plocationInfo, struct XiProject** links=nullptr, unsigned linkCount=0);

	static void InitilizeWorkspaceFileStructure(struct XiProject* pProj);
	static void InitilizeProjectFileStructure(struct XiProject* pProj);
	
	// LUA FILE GENERATION
	static void CreateLUAWorkspaceFile(struct XiProject* pProjWorkspace);
	static void CreateLUAProjectFile(struct XiProject* pProj, struct XiProject** links, unsigned linkCount);
	
	// XiProject File Generation
	static void CreateProjectFile(struct XiProject* pProj);

	static void CreateVisualStudioBuildFile(struct XiProject* pProj);
	static void BuildVisualStudioSolution(struct XiProject* pProj);

	static void CreateSourceFiles(struct XiProject* pProj, struct XiProject** links, unsigned linkCount);
	static void CompileProject(struct XiProject* pProj);

	static void InitProjectWithCompiler(struct XiProject* pProj);

	static void InitExeProjectFiles(struct XiProject* pProj, struct XiProject** links, unsigned linkCount);
	static void InitDllProjectFiles(struct XiProject* pProj, struct XiProject** links, unsigned linkCount);
	static void InitLibProjectFiles(struct XiProject* pProj, struct XiProject** links, unsigned linkCount);

private:
	static const std::string token_project;
	static const std::string token_workspace;
	static const std::string default_drive;
	static const std::string default_directory;
	static const std::string default_projectName;

};