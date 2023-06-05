#pragma once

#include "pch.h"
#include "defs.h"

#include "view.h"
#include "graph_renderer.h"



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

	void AddNode(std::string label, vec2 position, vec2 size);
	void ConnectNodes(Node* a, Node* b);

protected:
	void HandleZoom();

private:
	GraphRenderer renderer;

};

