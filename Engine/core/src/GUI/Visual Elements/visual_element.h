#pragma once
#include "pch.h"
#include "defs.h"



class VisualElement {
public:
	VisualElement();
	virtual ~VisualElement();

	
	void Draw(struct ImVec2 cursorPos);

	bool isWithinBounds(struct ImVec2 position, struct ImRect bounds);
	
	
	void Add(VisualElement* element);

	void Remove(VisualElement* element);

	virtual const std::string& Type() = 0;
	virtual const std::string& Guid() = 0;


	std::vector<VisualElement*> children;

	struct StyleSheet* styleSheet;
		
	struct ImVec2 AlignText(struct ImRect bounds, const std::string& text, enum TextAlignment alignment);
	
protected:
	virtual void Render(ImRect bounds) = 0;
	bool hover = false;
};


