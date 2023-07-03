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
	virtual void HandleContextMenu() = 0;

protected:
	void Render();

private:
	bool show;
	std::string name;
	int windowFlags;

	std::string xmlData;

	void RenderVisualElement(struct VisualElement* node);
	struct VisualElement* root = nullptr;

};