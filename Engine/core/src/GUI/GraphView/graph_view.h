#pragma once

#include "pch.h"
#include "defs.h"

#include "../view.h"

#include "glm/glm.hpp"
using namespace glm;

enum class NodeType {
	None,

	Float,
	Float2,
	Float3,
	Float4,

	Add, 
	Subtract,
	Multiply,
	Divide,

	_COUNT_
};

struct NodeData {
	std::string group;
	NodeType type;
};


class GraphView : public View
{

public:
	GraphView(const std::string& name);
	virtual ~GraphView() {};

	virtual void Update() override;
	virtual void Render() override;
	virtual void HandleContextMenu() override;



protected:
	std::string searchQuery;

private:
	static int SearchAndFilter(struct ImGuiInputTextCallbackData* data);

	void CreateNode(const std::string& name, NodeType type, struct ImVec2 position);

	class GraphRenderer* renderer;
	struct ImNodeEditorContext* nodeEditorCTX;

	static std::map<std::string, NodeData> nodeTable;
	static std::map<std::string, NodeData> searchResults;


};

