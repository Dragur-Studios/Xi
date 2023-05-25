#pragma once

#include "pch.h"

class iGame
{
public:
	iGame(const char* name, const char* directory) : name{ name }, directory{ directory } {};
	virtual ~iGame(){}

	virtual void OnInitilize() =0;
	virtual void OnTick() =0;
	virtual void OnShutdown() = 0;


	const std::string& GetName() const {
		return name;
	}
	const std::string& GetDirectory() const {
		return directory;
	}
	

	std::string name;
	std::string directory;

};


typedef iGame* (*XiGameFunc)();
