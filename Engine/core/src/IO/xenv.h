#pragma once

#include <string>
#include <fstream>
#include <map>

class XEnv {

public:
	static bool Load(const std::string& filepath);
	static std::string Get(const std::string& var);

private:
	static std::map<std::string, std::string> _variables;
};

