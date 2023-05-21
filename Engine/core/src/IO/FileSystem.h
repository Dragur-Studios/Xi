#pragma once

#include "pch.h"

class FileSystem
{
public:
	class File {
	public:
		static bool Create(const std::string& destination, const std::string& name);
		static bool Update(const std::string& filepath, const std::string& content);
		static bool Read(const std::string& filepath, std::string& content);
		static bool Delete(const std::string& filepath);
	};

	class FileUtils {
	public:
		static bool FindAndReplace(std::string& input, const std::string& token, const std::string& replacement, bool all = false);
		static bool Copy(const std::string& sourceFilepath, const std::string& destinationFilepath);
	};
	
	class Directory {
	public:
		static bool Create(const std::string& directoryPath, bool hidden = false);	
		static bool Update(const std::string& targetDirectory, const std::string& replacementDirectory);	
		static bool Read(const std::string& directoryPath, std::vector<std::string>& subDirectories);
		static bool Delete(const std::string& directoryPath);
	};
};

