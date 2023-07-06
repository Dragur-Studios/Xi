#pragma once

#include "pch.h"

class View 
{
public:
	View(const std::string& name, const std::string& filepath="", int flags = 0);
	virtual ~View();

	void Draw();

	void Show();
	void Hide();

	virtual void OnCreateGUI() {};

	void Add(class VisualElement* element);
	void Remove(class VisualElement* element);

protected:
	std::map<std::string, struct StyleSheet*> styleMap{};

private:
	void Render(class VisualElement* node, struct ImVec2& cursorPos);
	void RenderChild(VisualElement* node, ImVec2& cursorPos);

private:
	bool _show; 
	std::string _name;
	int _windowFlags;
	std::string _filepath;

	class VisualElement* _root = nullptr;

};