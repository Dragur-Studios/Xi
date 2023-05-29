#include "FileSystem.h"
#include <filesystem>


std::filesystem::path FileSystem::Directory::root;

bool FileSystem::File::Create(const std::string& destination, const std::string& name)
{
   
    if (!std::filesystem::exists(destination)) {
        Directory::Create(destination);
    }

    std::string filepath = destination + name;

    LOG_INFO("Creating File:\t" + filepath);

    std::ofstream file(filepath);

    if (!file) {
        LOG_ERROR("File Could Not Be Created!");
        return false;
    }

    LOG_SUCCESS("File Created Successfully.");
    file.close();

    return true;
}

bool FileSystem::File::Update(const std::string& filepath, const std::string& content)
{
    if (content.empty())
        return true;

    LOG_INFO("Aquiring File:\t" + filepath);

    std::ofstream file(filepath);

    if (!file) {
        LOG_ERROR("File Could Not Be Written To!");
        return false;
    }

    LOG_SUCCESS("File Aquired Successfully.");    
    LOG_INFO("Writing To File.");
    file << content;

    LOG_SUCCESS("File Write Succesfully.");
    file.close();
    return true;
}

bool FileSystem::File::Read(const std::string& filepath, std::string& content)
{

    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        content = "";
        return false;
    }

    content = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    return true;
}

bool FileSystem::File::Delete(const std::string& filepath)
{
    LOG_SUCCESS("Deleting File: " + filepath);
 
    try {
        std::filesystem::remove(filepath);
    }
    catch (const std::exception& e) {
        LOG_ERROR("Failed to delete file: " + filepath + "\n" +  e.what());;
        return false;
    }

    LOG_SUCCESS("File deleted successfully: " + filepath);
    return true;
}


bool FileSystem::FileUtils::FindAndReplace(std::string& input, const std::string& token, const std::string& replacement, bool all)
{
    size_t pos = input.find(token);

    // determine if the token actually exists.
    if (pos == std::string::npos) {
        LOG_ERROR("replacement Token(" + token + ") Not Found!");
        return false;
    }

    // should all occurances of the token be replaced?
    if (all) {

        // until the position is not valid find and replace every occurance of the token
        while (pos != std::string::npos)
        {
            input.replace(pos, token.length(), replacement);
            pos = input.find(token, pos + replacement.length());
        }
    }
    // if not replace only the first one found
    else {
        input.replace(pos, token.length(), replacement);
    }

    return true;
}

bool FileSystem::FileUtils::Copy(const std::string& sourceFilepath, const std::string& destinationFilepath)
{
    try {
        std::filesystem::copy(sourceFilepath, destinationFilepath);
        return true;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error copying file: " << ex.what() << std::endl;
        return false;
    }

}


bool FileSystem::Directory::Create(const std::string& directoryPath, bool hidden)
{
    std::filesystem::path path(directoryPath);

    LOG_INFO("Creating Directory: " + directoryPath);

    try {
        std::filesystem::create_directories(path);
        if (hidden) {
            SetFileAttributesA(directoryPath.c_str(), FILE_ATTRIBUTE_HIDDEN);
        }
    }
    catch (const std::exception& e) {
        LOG_ERROR("Failed to create directory: " + directoryPath + "\n" + e.what());
        return false;
    }

    LOG_SUCCESS("Directory created successfully: ");;
    return true;
}

bool FileSystem::Directory::Update(const std::string& oldPath, const std::string& newPath)
{
    try {
        std::filesystem::rename(oldPath, newPath);
    }
    catch (const std::exception& e) {
        LOG_ERROR("Failed to rename directory from: " + oldPath + " to: " + newPath + "\n" + e.what());
        return false;
    }

    LOG_SUCCESS("Directory renamed successfully from: " + oldPath + " to: " + newPath);
    return true;
}

bool FileSystem::Directory::Read(const std::string& filepath, std::vector<std::string>& content)
{
    LOG_INFO("Aquiring Directory Information");

    if (!std::filesystem::is_directory(filepath))
    {
        LOG_ERROR("Directory doesnt exist.");
        return false;   // dir doesnt exist
    }

    content = std::vector<std::string>();

    for (const auto& entry : std::filesystem::directory_iterator(filepath))
    {
        content.push_back(entry.path().string());
    }

    LOG_INFO("Directory Information Aquired, " + std::to_string(content.size()) + " Sub-Directories Found.");
    
    return true;
}

bool FileSystem::Directory::Delete(const std::string& directoryPath)
{
    if (!std::filesystem::is_directory(directoryPath)) {

        LOG_ERROR("Directory doesnt exist.");
        return false;   // dir doesnt exist
    }

    try {
        std::filesystem::remove_all(directoryPath);
        LOG_SUCCESS("Directory Removed Successfully");
        return true;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Failed to delete directory: " + directoryPath + "\n" + e.what());
        return false;
    }

}

std::filesystem::path FileSystem::Directory::SetWorkingDirectory(const std::string& filepath) {
    std::filesystem::path lastWD(std::filesystem::current_path());
    std::filesystem::path tempProjectPath(filepath);
    std::filesystem::current_path(tempProjectPath);
    LOG_INFO(std::filesystem::current_path().string());
    return lastWD;
}

void FileSystem::Directory::Push(const std::string& directoryPath)
{
    root = SetWorkingDirectory(directoryPath);
}

void FileSystem::Directory::Pop()
{
    std::filesystem::current_path(root);
}

