#pragma once

#include "pch.h"

class iGame
{
public:
	iGame() {};
	virtual ~iGame(){}

	virtual void OnInitilize() =0;
	virtual void OnTick() =0;
	virtual void OnShutdown() = 0;

	_declspec(dllexport) void SetName(const std::string& name) {
		this->name = name;
	}

	_declspec(dllexport) const std::string& GetName() const {
		return name;
	}

	std::string name;
	
};


typedef iGame* (*XiGameFunc)();
