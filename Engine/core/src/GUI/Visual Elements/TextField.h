#pragma once

#include "visual_element.h"

class TextField : public VisualElement
{
public:
	TextField();
	~TextField();

	virtual void OnCreateGUI() override;

private:
	std::string _data;

};

