#pragma once
#include "pch.h"
#include "defs.h"

#include "dependencies/imdom.h"

class VisualElement {
public:
	VisualElement(const std::string& type);
	VisualElement(const std::string& type, const std::string& name);
	virtual ~VisualElement();

	void OnEvent();
	
	bool isWithinBounds(ImVec2 position, ImRect bounds);
		
	void Add(VisualElement* element);
	void Remove(VisualElement* element);

	virtual void OnCreateGUI() = 0;
	
	// state 	
	bool _stop_propagation = false;
	bool _hover = false;
	bool _active = false;
	bool _focus = false;

	std::string _name = "";
	std::string _id = "";
	std::string _class = "";

	ImRect _bounds;

	std::vector<VisualElement*> _children;
protected:
	std::string _guid = "";
	virtual void OnClickCallback() {};

};


