#pragma once

#include "pch.h"

class XDocument {
public:
	XDocument(const std::string& modelPath, const std::string& stylePath);
	~XDocument();

	void Update();
	void Draw();

	void Add(class VisualElement* element);
	void Remove(class VisualElement* element);

	template<typename T>
	VisualElement* Q(const std::string& name);

	const std::string& to_string();

	void Compile();


private:
	template<typename T>
	class VisualElement* Query(class VisualElement* node, const std::string& name);

	void UpdateCursorPosition(class VisualElement* node, struct ImVec2& cursorPos);
	void DrawNode(class VisualElement* node, struct ImVec2& cursorPos);

	void Render(class VisualElement* node, struct ImVec2& cursorPos, int depth = 0);
	
	void PropagateEvents(class VisualElement* node);

private:
	class VisualElement* _root = nullptr;
	std::string _filepath;
	std::string _stylepath;
	
	bool _compile = false;

};

#include "xdocument.inl"
