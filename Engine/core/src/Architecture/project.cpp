#include "project.h"

XiProject::XiProject(const std::string& drive, const std::string& filepath, const std::string& name)
	: drive{drive}, filepath{filepath}, name{name}
{
}

XiProject::~XiProject()
{
}

const std::string& XiProject::GetRootFolder() const
{
	return drive + filepath + name + "\\";
}

const std::string& XiProject::GetName() const
{
	return name;
}
