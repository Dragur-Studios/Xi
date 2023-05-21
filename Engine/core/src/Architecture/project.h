#pragma once

#include "pch.h"
#include "defs.h"

class XiProject
{
public:
	XiProject(const std::string& drive, const std::string& filepath, const std::string& name);
	~XiProject();

	const std::string& GetRootFolder() const;
	const std::string& GetName() const;

private:
	std::string filepath;
	std::string name;
	std::string drive;

};

