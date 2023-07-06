#pragma once

#include "visual_element.h"
#include "util/guid.h"

constexpr float def_Width = 100.0f;
constexpr float def_Height = 30.0f;


class Button : public VisualElement
{
public:
	typedef void(*OnClick)();


public:
	Button(const std::string& label, OnClick clickfn);
	~Button();

	virtual void Render(struct ImRect bounds) override;

	virtual const std::string& Type() { return "Button"; };
	virtual const std::string& Guid() { return Guid::New(); };

	std::string _label;
	OnClick _onclick;

};