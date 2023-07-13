#pragma once

#include "visual_element.h"
#include "Util/guid.h"

class Group : public VisualElement
{
public:
	Group() ;
	~Group() ;

	virtual void OnCreateGUI() override;

private:
	std::string _text;
};