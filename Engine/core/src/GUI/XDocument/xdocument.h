#pragma once

#include "pch.h"

class XDocument {
public:
	XDocument();
	~XDocument();

	void Update();
	void Draw();

	void Add(class VisualElement* element);
	void Remove(class VisualElement* element);

	const std::string& to_string();

private:
	void UpdateCursorPosition(struct VisualElement* node, struct ImVec2& cursorPos);
	void DrawNode(class VisualElement* node, struct ImVec2& cursorPos);

	void Render(class VisualElement* node, struct ImVec2& cursorPos, int depth = 0);
	
	void PropagateEvents(class VisualElement* node);

private:
	class VisualElement* _root = nullptr;

};

