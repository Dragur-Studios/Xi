#pragma once

#include "visual_element.h"
#include "Util/guid.h"

class Group : public VisualElement
{
public:
	Group() ;
	~Group() ;

	virtual void Render(struct ImRect bounds) override;

	

	virtual const std::string& Type() { return "Container"; };
	virtual const std::string& Guid() { return Guid::New(); };

private:
	std::string _text;
};