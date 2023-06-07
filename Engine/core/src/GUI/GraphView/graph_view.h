#pragma once

#include "pch.h"
#include "defs.h"

#include "../view.h"

#include "glm/glm.hpp"
using namespace glm;



class GraphView : public View
{

public:
	GraphView(const std::string& name);
	virtual ~GraphView() {};

	virtual void Update() override;
	virtual void Render() override;
	virtual void HandleContextMenu() override;


private:
	class GraphRenderer* renderer;
	struct ImNodeEditorContext* nodeEditorCTX;

};

