#pragma once

#include "pch.h"

#include "Util/tinyxml2.h"

class View 
{
public:
	View(const std::string& name, const std::string& filepath="", int flags = 0);
	virtual ~View();

	void Draw();

	void Show();
	void Hide();

	void Add(class VisualElement* element);
	void Remove(class VisualElement* element);

private:
	void Render(class VisualElement* node);

private:
	bool _show; 
	std::string _name;
	int _windowFlags;
	std::string _filepath;

	struct VisualElement* _root = nullptr;
	tinyxml2::XMLDocument document;

};