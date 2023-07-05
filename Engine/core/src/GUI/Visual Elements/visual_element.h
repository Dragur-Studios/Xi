#pragma once
#include "pch.h"
#include "defs.h"

#include "visual_element.h"

#include "imgui/imgui.h"


class VisualElement {
public:
	///TODO! generate GUID
	VisualElement(ImVec2 position, ImVec2 size, const std::string& type) : _guid{ "####__GUID__" }, _position{ position }, _size{ size }, _type{ type } {};
	VisualElement() : _guid{ "####__GUID__" }, _position{ 0,0 }, _size{ 0,0 }{};
	
	virtual ~VisualElement() {};
	
	void Add(VisualElement* element) {
		children.push_back(element);
	}

	void Remove(VisualElement* element) {
		auto it = std::find(children.begin(), children.end(), element);
		if (it != children.end()) {
			std::remove(children.begin(), children.end(), element);
		}
	}

	virtual void Draw() = 0;

	template<typename T>
	T Q(std::string name = "") {

		for (auto& child : children)
		{
			bool override = name.empty();

			if (typeid(child) == typeid(T) && (child.id == name || override)) {
				return child;
			}

		}

		return {};
	}


	std::string _type;
	std::string _guid;
	// rect
	ImVec2 _position;
	ImVec2 _size;

	std::vector<VisualElement*> children;

};

class Group : public VisualElement
{
public:
	Group() : VisualElement({ -1, -1 }, { -1, -1 }, "Label") {};
	~Group() {};

	virtual void Draw() override
	{
	}

private:
	std::string _text;
};


class Button : public VisualElement
{
typedef void(*OnClick)();
public:
	Button(const std::string& label, OnClick clickfn) : VisualElement({ -1, -1 }, {-1, -1}, "Button"), _onclick{ clickfn }, _label{ label } {};
	Button(const std::string& label, ImVec2 position, ImVec2 size, OnClick clickfn) : VisualElement(position, size, "Button"), _onclick{ clickfn }, _label{ label } {};
	~Button() {};

	virtual void Draw() override 
	{
		if (ImGui::Button(_label.c_str(), _size)) {
			_onclick();
		}
	}

	std::string _label;
	OnClick _onclick;

};

class Label : public VisualElement 
{
public:
	Label(const std::string& text) : VisualElement({ -1, -1 }, { -1, -1 }, "Label"), _text{ text } {};
	~Label() {};

	virtual void Draw() override
	{
		ImGui::Text(_text.c_str());
	}

private:
	std::string _text;
};