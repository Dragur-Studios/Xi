#pragma once

#include "pch.h"
#include "defs.h"

enum class XiProjectType {
	EXE,
	DLL,
	LIB
};


struct XiProject
{
	std::string drive;
	std::string filepath;
	std::string workspace;
	std::string name;

	XiProjectType type;

};

