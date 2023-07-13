#include "xenv.h"

#include "file_helpers.h"
std::map<std::string, std::string> XEnv::_variables;

bool XEnv::Load(const std::string& filepath)
{

	std::ifstream file(filepath);
	if (!file.is_open())
		return false; 

	std::string line;
	
	while (std::getline(file, line)) {
		if (!line.empty()) {
			std::string var, val;
			if (ParseLine(line, var, val)) {
				_variables[var] = val;
			}
		}
	}

	file.close();
	return true;
}

std::string XEnv::Get(const std::string& var)
{
	auto it = _variables.find(var);

	if (it != _variables.end())
		return it->second;

	return "";
}

