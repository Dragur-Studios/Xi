#pragma once

#include "visual_element.h"


class Label : public VisualElement
{
public:
	Label(const std::string& text);
	~Label();

	virtual void OnCreateGUI() override;

private:
	std::string _text;
};