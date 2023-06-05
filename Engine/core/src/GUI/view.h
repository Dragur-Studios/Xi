#pragma once

#include "pch.h"

class View 
{
public:
	View(const std::string& name);
	virtual ~View();

	void Draw();

	void Show();
	void Hide();

protected:
	virtual void Update() = 0;
	virtual void Render() {};
	virtual void HandleContextMenu() = 0;

protected:
	bool show;
	std::string name;
	int windowFlags;

};