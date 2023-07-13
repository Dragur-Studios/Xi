#pragma once

#include "visual_element.h"
#include "util/guid.h"
#include <functional>

constexpr float def_Width = 100.0f;
constexpr float def_Height = 30.0f;


class Button : public VisualElement
{
public:
	using OnClick = std::function<void()>;


public:
	Button(const std::string& label, OnClick clickfn);
	Button(const std::string& label, const std::string& name, OnClick clickfn);
	
	~Button();

	virtual void OnCreateGUI() override;
	virtual void OnClickCallback() override;

	std::string _label;
	OnClick _onclick;

};