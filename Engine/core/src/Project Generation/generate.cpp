#include "generate.h"

#include <filesystem>
#include "IO/FileSystem.h"
#include "architecture/project.h"

const std::string ProjectGenerator::token_workspace = "ws__________";
const std::string ProjectGenerator::token_project = "pj__________";

const std::string ProjectGenerator::default_drive = "C:\\";
const std::string ProjectGenerator::default_directory = "Xi\\Projects\\";
const std::string ProjectGenerator::default_projectName = "New Project";

std::string ProjectGenerator::projectName = ProjectGenerator::default_projectName;
std::string ProjectGenerator::drive = ProjectGenerator::default_drive;
std::string ProjectGenerator::directory = ProjectGenerator::default_directory;

std::filesystem::path SetWorkingDirectory(const std::string& filepath) {
    std::filesystem::path lastWD(std::filesystem::current_path());
    std::filesystem::path tempProjectPath(filepath);
    std::filesystem::current_path(tempProjectPath);
    LOG_INFO(std::filesystem::current_path().string());
    return lastWD;
}

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

XiProject* ProjectGenerator::GenerateProject(ProjectGeneratorLocationInfo* plocationInfo)
{

    SetGenerationLocation(plocationInfo);
    InitilizeProjectFileStructure();
    CreateControlFile();
    CreateProjectFile();
    CreateVisualStudioBuildFile();
    BuildVisualStudioSolution();
    CreateSourceFiles();

    XiProject* project = new XiProject();
    
    project->drive = plocationInfo->Drive;
    project->name = plocationInfo->ProjectName;
    project->filepath = plocationInfo->Filepath;

    BuildVisualStudioProject(project);
    
    return project;
}

void ProjectGenerator::SetGenerationLocation(ProjectGeneratorLocationInfo* plocationInfo)
{
    LOG_INFO("Updating Project Generation Loction");
    
    LOG_INFO("{")
    drive = plocationInfo->Drive;
    LOG_INFO("\tDrive:\t" + drive);
    directory = plocationInfo->Filepath;
    LOG_INFO("\tDirectory:\t" + directory);
    projectName = toPascalCase(plocationInfo->ProjectName);
    LOG_INFO("\tProjectName:\t" + projectName);
    LOG_INFO("}")
}

void ProjectGenerator::InitilizeProjectFileStructure()
{
    std::string root = drive + directory + projectName + "\\";

    LOG_INFO("Initilizing Project at " + root)

    std::map<std::string, bool> directories;
    directories.emplace(root, false);
    directories.emplace(root + "Source\\", false);
    directories.emplace(root + "Build\\", false);
    directories.emplace(root + "_\\", true);

    for (const auto kvp : directories)
    {
        CHECK_RESULT(FileSystem::Directory::Create(kvp.first, kvp.second));
    }

    LOG_SUCCESS("Initilize Project File Structure Success.");
}

void ProjectGenerator::CreateControlFile()
{
    std::string root = drive + directory + projectName + "\\";

    LOG_INFO("Control File Creation Started.");
    std::string controlTemplateTxt;

    CHECK_RESULT(FileSystem::File::Read("resources/templates/project_control_file.txt", controlTemplateTxt));

    CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(controlTemplateTxt, token_workspace, "\"" + projectName + "\""));
    CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(controlTemplateTxt, token_project, "\"" + projectName + "\""));
    
    CHECK_RESULT(FileSystem::File::Create(root, "premake5.lua"));
    
    std::filesystem::path lastWD(SetWorkingDirectory(root));

    CHECK_RESULT(FileSystem::File::Update("premake5.lua", controlTemplateTxt));

    LOG_INFO("Control File Creation Completed Successfully.");

    std::filesystem::current_path(lastWD);

}

void ProjectGenerator::CreateProjectFile() {
    LOG_INFO("Project File Creation Started.");
    
    std::string root = drive + directory + projectName + "\\";

    std::string extension = ".xiProject";

    CHECK_RESULT(FileSystem::File::Create(root, projectName + extension));
    
    std::stringstream ss;
    
    ss << projectName << "\n"
        << root << "\n" <<
        "\0";

    CHECK_RESULT(FileSystem::File::Update(root + projectName + extension, ss.str()));

    LOG_INFO("Project File Created Succssfully.");
}

void ProjectGenerator::CreateVisualStudioBuildFile()
{
    LOG_INFO("Porject Build File Creation Started.");

    std::string root = drive + directory + projectName + "\\";
    std::filesystem::path lastWD(SetWorkingDirectory(root));


    CHECK_RESULT(FileSystem::File::Create("_\\", "generate_project.bat"));

    std::string buildCommands = "";
    buildCommands += "call _\\premake5\\premake5.exe vs2022\n";
    //buildCommands += "call xcopy /E /I \"assets\\\" \"tools / editor / assets\\\" /Y\n";
    
    CHECK_RESULT(FileSystem::File::Update(root + "_\\" + "generate_project.bat", buildCommands));
    std::filesystem::current_path(lastWD);

    CHECK_RESULT(FileSystem::FileUtils::Copy("resources\\executables\\premake5", root + "_\\premake5"));

    LOG_SUCCESS("Project Build File Created Succsfully.");



}

void ProjectGenerator::BuildVisualStudioSolution()
{
    LOG_INFO("Visual Studio Solution Generation Started.");

    std::string root = drive + directory + projectName + "\\";
    std::filesystem::path lastWD(SetWorkingDirectory(root));


    std::string buildCommand = "call \"_\\generate_project.bat\" 0";
    
    int res = system(buildCommand.c_str());

    if (res == 0)
    {
        LOG_SUCCESS("Visual Studio Solution Generation Success.");
    }
    else {
        LOG_ERROR("Faild to build Visual Studio Solution.");
    }

    std::filesystem::current_path(lastWD);
}

void ProjectGenerator::BuildVisualStudioProject(XiProject* pProjectData)
{
    std::string root = pProjectData->drive + pProjectData->filepath + pProjectData->name + "\\";
    std::string solution = pProjectData->name + ".sln";

    std::string buildpath = "C:\\\"Program Files\"\\\"Microsoft Visual Studio\"\\2022\\Enterprise\\VC\\Auxiliary\\Build\\vcvars64.bat";
    LOG_INFO("Attepting to Run: "+ buildpath + "\n" + root + solution);
    
    // Construct the build command
    
    
    
    std::string command = "call cl"+ buildpath + " \"" + root  + solution + "\"";

    // Run the build command using the system function
    
    int result = std::system(command.c_str());

    // Check the result of the system command
    if (result == 0)
    {
        LOG_SUCCESS("\tTarget Visual Studio Project Build Successful");
    }
    else
    {
        LOG_ERROR("\tTarget Visual Studio Project Build Failed");
    }
}


void ProjectGenerator::CreateSourceFiles()
{
    LOG_INFO("Adding Source Files");

    std::string template_game_file_h;
    std::string template_game_file_cpp;

    CHECK_RESULT(FileSystem::File::Read("resources/templates/game_file_h.txt", template_game_file_h));
    CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(template_game_file_h, "__game_name__", projectName, true));
    
    CHECK_RESULT(FileSystem::File::Read("resources/templates/game_file_cpp.txt", template_game_file_cpp));
    CHECK_RESULT(FileSystem::FileUtils::FindAndReplace(template_game_file_cpp, "__game_name__", projectName, true));
    
    std::string nameCPP = projectName + ".cpp";
    std::string nameH = projectName + ".h";

    std::string root = drive + directory + projectName + "\\";
    std::filesystem::path lastWD(SetWorkingDirectory(root));


    CHECK_RESULT(FileSystem::File::Create("Source\\src\\", nameCPP));
    CHECK_RESULT(FileSystem::File::Update("Source\\src\\" + nameCPP, template_game_file_cpp));

    CHECK_RESULT(FileSystem::File::Create("Source\\src\\",  nameH));
    CHECK_RESULT(FileSystem::File::Update("Source\\src\\" + nameH, template_game_file_h));


    std::filesystem::current_path(lastWD);

    LOG_SUCCESS("Hello Source Files Success");

}


