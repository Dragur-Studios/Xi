#pragma once


#include "visual_element.h"
#include "Util/guid.h"


class Label : public VisualElement
{
public:
	Label(const std::string& text);
	~Label();

	virtual void Render(ImRect bounds) override;


	virtual const std::string& Type() { return "Label"; };
	virtual const std::string& Guid() { return Guid::New(); };

private:
	std::string _text;
};