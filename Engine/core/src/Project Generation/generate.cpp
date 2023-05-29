#include "generate.h"

#include <filesystem>
#include "IO/FileSystem.h"
#include "architecture/project.h"

const std::string ProjectGenerator::token_workspace = "ws__________";
const std::string ProjectGenerator::token_project = "pj__________";

const std::string ProjectGenerator::default_drive = "C:\\";
const std::string ProjectGenerator::default_directory = "Xi\\Projects\\";
const std::string ProjectGenerator::default_projectName = "New Project";

std::string toPascalCase(const std::string& str)
{
    std::string result;

    bool capitalizeNext = true;

    for (char c : str)
    {
        if (std::isalpha(c))
        {
            if (capitalizeNext)
            {
                result += std::toupper(c);
                capitalizeNext = false;
            }
            else
            {
                result += std::tolower(c);
            }
        }
        else if (std::isspace(c) || c == '_')
        {
            capitalizeNext = true;
        }
    }

    return result;
}

void ProjectGenerator::GenerateProject(ProjectGeneratorLocationInfo* plocationInfo)
{
    XiProject* workspace = CreateXiWorkspace(plocationInfo);

    //// GAME DLL 
    auto dll_createInfo = *plocationInfo;
    dll_createInfo.Type = XiProjectType::DLL;    
    XiProject* dll = CreateXiProject(&dll_createInfo);

    // EXECUTABLE
    auto exe_createInfo = *plocationInfo;
    exe_createInfo.Type = XiProjectType::EXE;
    exe_createInfo.ProjectName = "Xi";
    XiProject* exe = CreateXiProject(&exe_createInfo, &dll, 1);


    CreateLUAWorkspaceFile(workspace);
    BuildVisualStudioSolution(workspace);
    
}

XiProject* ProjectGenerator::CreateXiProject(ProjectGeneratorLocationInfo* plocationInfo, XiProject** links, unsigned linkCount)
{
    LOG_INFO("Updating Project Generation Loction");

    XiProject* proj = new XiProject();
    proj->drive = plocationInfo->Drive;
    proj->name = plocationInfo->ProjectName;
    proj->workspace = plocationInfo->WorkspaceDirectory;
    proj->filepath = plocationInfo->Filepath;
    proj->type = plocationInfo->Type;

    InitilizeProjectFileStructure(proj);
    CreateLUAProjectFile(proj, links, linkCount);
    CreateSourceFiles(proj, links, linkCount);


    return proj;

}

XiProject* ProjectGenerator::CreateXiWorkspace(ProjectGeneratorLocationInfo* plocationInfo)
{
    LOG_INFO("Updating Project Generation Loction");

    XiProject* proj = new XiProject();
    proj->drive =plocationInfo->Drive;
    proj->name = plocationInfo->ProjectName;
    proj->workspace = plocationInfo->WorkspaceDirectory;
    proj->filepath = plocationInfo->Filepath;
    proj->type = plocationInfo->Type;


    InitilizeWorkspaceFileStructure(proj);
    CreateVisualStudioBuildFile(proj);

    return proj;

}

void ProjectGenerator::InitilizeWorkspaceFileStructure(XiProject* pProj)
{
    std::string root = workspace_root(pProj);

    LOG_INFO("Initilizing Workspace at " + root)

    std::map<std::string, bool> directories;
    directories.emplace(root, false);
    directories.emplace(root + "Build\\", false);
    directories.emplace(root + "_\\", true);

    for (const auto kvp : directories)
    {
        CHECK_RESULT(FileSystem::Directory::Create(kvp.first, kvp.second));
    }

    LOG_SUCCESS("Initilize Project File Structure Success.");

}

void ProjectGenerator::InitilizeProjectFileStructure(XiProject* pProj)
{
    std::string root = project_root(pProj);

    LOG_INFO("Initilizing Project at " + root)

    std::map<std::string, bool> directories;
    directories.emplace(root, false);
   // directories.emplace(root + "Source\\", false);

    for (const auto kvp : directories)
    {
        CHECK_RESULT(FileSystem::Directory::Create(kvp.first, kvp.second));
    }

    LOG_SUCCESS("Initilize Project File Structure Success.");
}

void ProjectGenerator::CreateLUAWorkspaceFile(XiProject* pWorkspace)
{
    std::string root = workspace_root(pWorkspace);

    LOG_INFO("LUA Workspace File Creation Started.");
    std::string workspaceTemplateText;

    CHECK_RESULT(FileSystem::File::Read("resources/templates/workspace_template.txt", workspaceTemplateText));

    CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(workspaceTemplateText, token_workspace, "\"" + pWorkspace->name + "\""));
    CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(workspaceTemplateText, "__NAME__", "\"" + pWorkspace->name + "\""));
 
    CHECK_RESULT(FileSystem::File::Create(root, "premake5.lua"));

    FileSystem::Directory::Push(root);

    CHECK_RESULT(FileSystem::File::Update("premake5.lua", workspaceTemplateText));

    LOG_INFO("LUA Workspace FileCreation Completed Successfully.");

    FileSystem::Directory::Pop();

}

void ProjectGenerator::CreateLUAProjectFile(XiProject* pProj, XiProject** links, unsigned linkCount)
{
    std::string root = project_root(pProj);
    LOG_INFO("Control File Creation Started.");
    std::string controlTemplateTxt;

    CHECK_RESULT(FileSystem::File::Read("resources/templates/project_template.txt", controlTemplateTxt));

    std::string temp = "Z:/Dev/Xi/";

    std::string core_inc = temp + "Engine/Core/src/";
    std::string libDirs_core = temp + "Build/Engine/";
    std::string links_core = "\"Core\"";

    std::string includes =  "\"" + core_inc + "\"," ;
    for (size_t i = 0; i < linkCount; i++)
    {
        includes += "\"../" + links[i]->name + "/src" + "\",";
    }




    CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(controlTemplateTxt, "__Includes__", includes));
    
    std::string libDirs = "\"" + libDirs_core + "\", ";
    libDirs += "\"../Build/\",";

    CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(controlTemplateTxt, "__LibDirs__", libDirs));

   
    std::string linksStr = links_core + ",";
    for (size_t i = 0; i < linkCount; i++)
    {
        linksStr += "\"" + links[i]->name + "\",";
    }

    CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(controlTemplateTxt, "__Links__", linksStr));

    CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(controlTemplateTxt, token_project, "\"" + pProj->name + "\""));

    
    switch (pProj->type)
    {
    case XiProjectType::EXE: {
        #ifndef _DEBUG
        std::string exe = "WindowedApp";
        #else
        std::string exe = "ConsoleApp";
        #endif
        CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(controlTemplateTxt, "__TYPE__", exe));

    }
        break;
    case XiProjectType::DLL:
        CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(controlTemplateTxt, "__TYPE__", "SharedLib"));
        break;
    case XiProjectType::LIB:
        CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(controlTemplateTxt, "__TYPE__", "StaticLib"));
        break;

    }

    
    
    CHECK_RESULT(FileSystem::File::Create(root, "premake5.lua"));
    
    FileSystem::Directory::Push(root);

    CHECK_RESULT(FileSystem::File::Update("premake5.lua", controlTemplateTxt));

    LOG_INFO("Control File Creation Completed Successfully.");

    FileSystem::Directory::Pop();

}

void ProjectGenerator::CreateProjectFile(XiProject* pProj) {
    LOG_INFO("Project File Creation Started.");
    
    std::string root = workspace_root(pProj);

    std::string extension = ".xiProject";

    CHECK_RESULT(FileSystem::File::Create(root, pProj->name + extension));
    
    std::stringstream ss;
    
    ss << pProj->name << "\n"
        << root << "\n" <<
        "\0";

    CHECK_RESULT(FileSystem::File::Update(root + pProj->name + extension, ss.str()));

    LOG_INFO("Project File Created Succssfully.");
}

void ProjectGenerator::CreateVisualStudioBuildFile(XiProject* pProj)
{
    LOG_INFO("Porject Build File Creation Started.");
    
    std::string root = workspace_root(pProj);

    FileSystem::Directory::Push(root);

    CHECK_RESULT(FileSystem::File::Create("_\\", "generate_project.bat"));

    std::string buildCommands = "";
    buildCommands += "call _\\premake5\\premake5.exe vs2022\n";
    
    CHECK_RESULT(FileSystem::File::Update(root + "_\\" + "generate_project.bat", buildCommands));

    FileSystem::Directory::Pop();

    CHECK_RESULT(FileSystem::FileUtils::Copy("resources\\executables\\premake5", root + "_\\premake5"));

    LOG_SUCCESS("Project Build File Created Succsfully.");



}

void ProjectGenerator::BuildVisualStudioSolution(XiProject* pProj)
{
    LOG_INFO("Visual Studio Solution Generation Started.");

    std::string root = workspace_root(pProj);

    //std::filesystem::path lastWD(SetWorkingDirectory(root));
    FileSystem::Directory::Push(root);


    std::string buildCommand = "call \"_\\generate_project.bat\" 0";
    
    int res = system(buildCommand.c_str());

    if (res == 0)
    {
        LOG_SUCCESS("Visual Studio Solution Generation Success.");
    }
    else {
        LOG_ERROR("Faild to build Visual Studio Solution.");
    }

    FileSystem::Directory::Pop();

}

void ProjectGenerator::InitProjectWithCompiler(XiProject* pProj) {
  
    std::string root = workspace_root(pProj);

    // Construct the build command
    std::string template_build_file;

    switch (pProj->type)
    {
    case XiProjectType::DLL:
        CHECK_RESULT(FileSystem::File::Read("resources/executables/compile_dll.bat", template_build_file)); //<---- TODO!! this should be a pointer to this ref 
        CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(template_build_file, "__NAME__", pProj->name, true));
        break;
    case XiProjectType::EXE:
        CHECK_RESULT(FileSystem::File::Read("resources/executables/compile_exe.bat", template_build_file)); //<---- TODO!! this should be a pointer to this ref 
        CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(template_build_file, "__NAME__", pProj->name, true));
        break;
    case XiProjectType::LIB:
        CHECK_RESULT(FileSystem::File::Read("resources/executables/compile_lib.bat", template_build_file)); //<---- TODO!! this should be a pointer to this ref 
        CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(template_build_file, "__NAME__", pProj->name, true));
        break;
    }

    FileSystem::Directory::Push(root);

    switch (pProj->type)
    {
    case XiProjectType::EXE:
      
        CHECK_RESULT(FileSystem::File::Create("./_/", "compile_exe.bat"));
        CHECK_RESULT(FileSystem::File::Update("./_/compile_exe.bat", template_build_file));

        break;
    case XiProjectType::DLL:

        CHECK_RESULT(FileSystem::File::Create("./_/", "compile_dll.bat"));
        CHECK_RESULT(FileSystem::File::Update("./_/compile_dll.bat", template_build_file));

        break;
    case XiProjectType::LIB:

        CHECK_RESULT(FileSystem::File::Create("./_/", "compile_lib.bat"));
        CHECK_RESULT(FileSystem::File::Update("./_/compile_lib.bat", template_build_file));

        break;
    }
    
    FileSystem::Directory::Pop();

}

void ProjectGenerator::CompileProject(XiProject* pProj)
{
    LOG_INFO("Creating Compilation Module");

    std::string root = workspace_root(pProj);
    // PRE COMPILE 
    FileSystem::Directory::Push(root);

    int result = 0;
    switch (pProj->type)
    {
    case XiProjectType::EXE:
        result = std::system(".\\_\\compile_exe.bat");
        break;
    case XiProjectType::DLL:
        result = std::system(".\\_\\compile_dll.bat");
        break;
    case XiProjectType::LIB:
        result = std::system(".\\_\\compile_lib.bat");
        break;
    }

    if (result != 0) {
        LOG_ERROR("Project Could Not Be compiled!");
        return;
    }

    FileSystem::Directory::Pop();

    LOG_SUCCESS("Project Compiled Succses");
}

void ProjectGenerator::InitExeProjectFiles(XiProject* pProj, struct XiProject** links, unsigned linkCount) {
    std::string main_file_cpp;

    CHECK_RESULT(FileSystem::File::Read("resources/templates/main_cpp.txt", main_file_cpp));

    CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(main_file_cpp, "__name__", links[0]->name, true));

    std::string root = project_root(pProj);

    FileSystem::Directory::Push(root);

    CHECK_RESULT(FileSystem::File::Create("src\\",  "main.cpp"));
    CHECK_RESULT(FileSystem::File::Update("src\\main.cpp", main_file_cpp));

    FileSystem::Directory::Pop();
}

void ProjectGenerator::InitDllProjectFiles(XiProject* pProj, struct XiProject** links, unsigned linkCount) {
    std::string template_game_file_h;
    std::string template_game_file_cpp;

    CHECK_RESULT(FileSystem::File::Read("resources/templates/game_h_template.txt", template_game_file_h));
    CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(template_game_file_h, "__game_name__", pProj->name, true));

    CHECK_RESULT(FileSystem::File::Read("resources/templates/game_cpp_template.txt", template_game_file_cpp));
    CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(template_game_file_cpp, "__game_name__", pProj->name, true));

    std::string nameCPP = pProj->name + ".cpp";
    std::string nameH = pProj->name + ".h";

    std::string root = project_root(pProj);

    FileSystem::Directory::Push(root);

    CHECK_RESULT(FileSystem::File::Create("src\\", nameCPP));
    CHECK_RESULT(FileSystem::File::Update("src\\" + nameCPP, template_game_file_cpp));

    CHECK_RESULT(FileSystem::File::Create("src\\", nameH));
    CHECK_RESULT(FileSystem::File::Update("src\\" + nameH, template_game_file_h));

    FileSystem::Directory::Pop();

}

void ProjectGenerator::InitLibProjectFiles(XiProject* pProj, struct XiProject** links, unsigned linkCount) {
    std::string template_game_file_h;
    std::string template_game_file_cpp;

    CHECK_RESULT(FileSystem::File::Read("resources/templates/game_h_template.txt", template_game_file_h));
    CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(template_game_file_h, "__game_name__", pProj->name, true));

    CHECK_RESULT(FileSystem::File::Read("resources/templates/game_cpp_template.txt", template_game_file_cpp));
    CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(template_game_file_cpp, "__game_name__", pProj->name, true));

    std::string nameCPP = pProj->name + ".cpp";
    std::string nameH = pProj->name + ".h";

    std::string root = project_root(pProj);

    FileSystem::Directory::Push(root);

    CHECK_RESULT(FileSystem::File::Create("src\\", nameCPP));
    CHECK_RESULT(FileSystem::File::Update("src\\" + nameCPP, template_game_file_cpp));

    CHECK_RESULT(FileSystem::File::Create("src\\", nameH));
    CHECK_RESULT(FileSystem::File::Update("src\\" + nameH, template_game_file_h));

    FileSystem::Directory::Pop();
}

void ProjectGenerator::CreateSourceFiles(XiProject* pProj, struct XiProject** links, unsigned linkCount)
{
    LOG_INFO("Adding Source Files");

    switch (pProj->type)
    {
    case XiProjectType::EXE:
        InitExeProjectFiles(pProj, links, linkCount);
        break;

    case XiProjectType::DLL:
        InitDllProjectFiles(pProj, links, linkCount);
        break;

    case XiProjectType::LIB:
        InitLibProjectFiles(pProj, links, linkCount);
        break;
    }

    LOG_SUCCESS("Source Files Added Success");

}


