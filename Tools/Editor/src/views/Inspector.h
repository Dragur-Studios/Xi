#pragma once

#include "pch.h"
#include "GUI/view.h"

class Inspector : public View
{
public:
	Inspector();
	~Inspector();

	virtual void Update() override;
	virtual void HandleContextMenu() override;

};

