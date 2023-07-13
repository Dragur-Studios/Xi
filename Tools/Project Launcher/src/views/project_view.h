#pragma once

#include "GUI/view.h"

class ProjectsView : public View
{
public:
	ProjectsView();
	virtual ~ProjectsView();

	virtual void HandleContextMenu();

public:
	virtual void OnCreateGUI() override;
	virtual void OnGUI() override;

};

