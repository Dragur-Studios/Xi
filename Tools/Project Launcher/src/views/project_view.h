#pragma once
#include "pch.h"
#include "defs.h"

#include "GUI/view.h"
#include "GUI/Visual Elements/visual_element.h"

class ProjectsView : public View
{
public:
	ProjectsView();
	virtual ~ProjectsView();

	static void CreateProject();
	virtual void OnCreateGUI() override;
	virtual void HandleContextMenu();
	static int counter;



};

