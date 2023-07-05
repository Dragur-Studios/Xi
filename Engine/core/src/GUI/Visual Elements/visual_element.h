#pragma once
#include "pch.h"
#include "defs.h"

#include "visual_element.h"

#include "imgui/imgui.h"

#include "Util/guid.h"


struct ImRect {
	ImVec2 start;
	ImVec2 end;
};

struct ImColorState {
	ImU32 normal = 0;
	ImU32 active = 0;
	ImU32 hover = 0;
};

class VisualElement {
public:
	///TODO! generate GUID
	VisualElement()
	{ };

	virtual ~VisualElement() {};

	
	void Draw() {


		ImDrawList* drawList = ImGui::GetWindowDrawList();

		//offset startposition by the padding, the margin, and the border sizes
		auto margin = styleSheet.margin;
		auto border = styleSheet.border;
		auto padding = styleSheet.padding;
		
		auto displaySize = ImGui::GetIO().DisplaySize;
		
		// draw margin area
		{
			ImVec2 start = ImGui::GetCursorScreenPos();
			ImVec2 end = start;
			end.x += margin.x + border.x + padding.x + styleSheet.width;
			end.y += margin.y + border.y + padding.y + styleSheet.height;

			drawList->AddRectFilled(start, end, 0);
		}
		
		//draw border area
		{
			ImVec2 start = ImGui::GetCursorScreenPos();
			start.x += margin.x / 2.0f;
			start.y += margin.y / 2.0f;

			ImVec2 end = start;
			end.x += border.x + padding.x + styleSheet.width;
			end.y += border.y + padding.y + styleSheet.height;

			drawList->AddRectFilled(start, end, styleSheet.border_color.normal);
		}

		//draw padding area
		{
			ImVec2 start = ImGui::GetCursorScreenPos();
			start.x += (margin.x / 2.0f) + (border.x / 2.0f);
			start.y += (margin.y / 2.0f) + (border.y / 2.0f);

			ImVec2 end = start;
			end.x += padding.x + styleSheet.width;
			end.y += padding.y + styleSheet.height;
			
			ImColor background = hover ? styleSheet.background_color.hover : styleSheet.background_color.normal;

			drawList->AddRectFilled(start, end, background);
		}


		//draw content area
		{
			ImVec2 start = ImGui::GetCursorScreenPos();
			start.x += (padding.x / 2.0f) + (margin.x / 2.0f) + (border.x / 2.0f);
			start.y += (padding.y / 2.0f) + (margin.y / 2.0f) + (border.y / 2.0f);

			ImVec2 end = start;
			end.x += styleSheet.width;
			end.y += styleSheet.height;

			Render({start, end});
		}

	};

	bool isWithinBounds(ImVec2 position, ImRect bounds) {
		
		// Flip the Y-axis position
	
		if (position.x >= bounds.start.x && position.x <= bounds.end.x &&
			position.y >= bounds.start.y && position.y <= bounds.end.y)
		{
			return true;
		}
		return false;
	}
	
	void Add(VisualElement* element) {
		children.push_back(element);
	}

	void Remove(VisualElement* element) {
		auto it = std::find(children.begin(), children.end(), element);
		if (it != children.end()) {
			//std::remove(children.begin(), children.end(), element);
			std::erase(children, element);
		}
	}

	virtual const std::string& Type() = 0;
	virtual const std::string& Guid() = 0;

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

	// rect
	ImVec2 _position;

	std::vector<VisualElement*> children;

	struct
	{
		float width = 0;
		float height = 0;

		ImVec4 padding	= { 0, 0, 0, 0 };
		ImVec4 margin	= { 0, 0, 0, 0 };

		ImVec4 border	= { 0, 0, 0, 0 };
		ImColorState border_color;
		
		ImColorState font_color;
		ImColorState background_color;
		
	}styleSheet;

protected:
	virtual void Render(ImRect bounds) = 0;
	bool hover = false;
};

class Group : public VisualElement
{
public:
	Group() {};
	~Group() {};

	virtual void Render(ImRect bounds) override
	{
	}

	virtual const std::string& Type() { return "Container"; };
	virtual const std::string& Guid() { return Guid::New(); };

private:
	std::string _text;
};


constexpr float def_Width = 100.0f;
constexpr float def_Height = 30.0f;


class Button : public VisualElement
{
public:
	typedef void(*OnClick)();


public:
	Button(const std::string& label, OnClick clickfn)
		: _label{ label }, _onclick{ clickfn }
	{};

	~Button() {};

	virtual void Render(ImRect bounds) override
	{
		ImVec2 mp = ImGui::GetMousePos();
		
		hover = isWithinBounds(mp, bounds);
		
		ImDrawList* drawList = ImGui::GetWindowDrawList();

		ImColor background = hover ? styleSheet.background_color.hover : styleSheet.background_color.normal;
		ImColor font = hover ? styleSheet.font_color.hover : styleSheet.font_color.normal;

		drawList->AddRectFilled(bounds.start, bounds.end, background);

		if (ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left) && hover) {
			_onclick();
		}

		drawList->AddText(bounds.start, font, _label.c_str());
		
	}

	virtual const std::string& Type() { return "Button"; };
	virtual const std::string& Guid() { return Guid::New(); };

	std::string _label;
	OnClick _onclick;

};

class Label : public VisualElement
{
public:
	Label(const std::string& text)
		: _text{ text }
	{};
	~Label() {};

	virtual void Render(ImRect bounds) override
	{
		ImGui::Text(_text.c_str());
	}

	virtual const std::string& Type() { return "Label"; };
	virtual const std::string& Guid() { return Guid::New(); };

private:
	std::string _text;
};