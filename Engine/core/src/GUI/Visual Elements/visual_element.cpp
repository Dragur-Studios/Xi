#include "visual_element.h"


#include "Util/guid.h"

#include "gui/xss.h"
#include "gui/stylesheet.h"

#include "imgui/imgui.h"


VisualElement::VisualElement()

{

	styleSheet = new StyleSheet();


};

VisualElement::~VisualElement()
{
	delete styleSheet;
}

void VisualElement::Draw(ImVec2 cursorPos)
{

	ImDrawList* drawList = ImGui::GetWindowDrawList();

	//offset startposition by the padding, the margin, and the border sizes
	auto margin = styleSheet->margin;
	auto border = styleSheet->border;
	auto padding = styleSheet->padding;
	auto shadow = styleSheet->shadow;

	auto displaySize = ImGui::GetIO().DisplaySize;

	// draw shadow area
	{
		ImVec2 start = cursorPos;
		start.x += margin.x / 2.0f;
		start.y += margin.y / 2.0f;

		ImVec2 end = start;
		end.x += shadow.x + border.x + padding.x + styleSheet->width;
		end.y += shadow.y + padding.y + styleSheet->height;

		drawList->AddRectFilled(start, end, styleSheet->shadow_color.normal, styleSheet->rounding);
	}

	//draw content area
	{
		ImVec2 start = cursorPos;
		start.x += (margin.x / 2.0f) + (border.x / 2.0f);
		start.y += (margin.y / 2.0f) + (border.y / 2.0f);

		ImVec2 end = start;
		end.x += padding.x + styleSheet->width;
		end.y += padding.y + styleSheet->height;

		Render({ start, end });
	}

	// draw border area
	{
		ImVec2 start = cursorPos;
		start.x += margin.x / 2.0f;
		start.y += margin.y / 2.0f;

		ImVec2 end = start;
		end.x += border.x + padding.x + styleSheet->width;
		end.y += border.y + padding.y + styleSheet->height;

		drawList->AddRect(start, end, styleSheet->border_color.normal, styleSheet->rounding, 0, styleSheet->border.x);
	}

};
bool VisualElement::isWithinBounds(ImVec2 position, ImRect bounds)
{
	if (position.x >= bounds.start.x && position.x <= bounds.end.x &&
		position.y >= bounds.start.y && position.y <= bounds.end.y)
	{
		return true;
	}
	return false;
}

void VisualElement::Add(VisualElement* element)
{
	children.push_back(element);
}

void VisualElement::Remove(VisualElement* element)
{
	auto it = std::find(children.begin(), children.end(), element);
	if (it != children.end()) {
		//std::remove(children.begin(), children.end(), element);
		std::erase(children, element);
	}
}

ImVec2 VisualElement::AlignText(ImRect bounds, const std::string& text, TextAlignment alignment)
{
	auto textPos = bounds.start;

	auto size = ImGui::CalcTextSize(text.c_str());
	auto center = ImVec2((bounds.end.x + bounds.start.x) / 2.0f, (bounds.end.y + bounds.start.y) / 2.0f);

	switch (alignment)
	{
	case TextAlignment::Top_Left:
		textPos.x += styleSheet->padding.x;
		textPos.y += styleSheet->padding.y;
		break;
	case TextAlignment::Top_Middle:
		textPos.y += styleSheet->padding.y;
		textPos.x = center.x - (size.x / 2.0f);
		break;
	case TextAlignment::Top_Right:
		textPos.y += styleSheet->padding.y;
		textPos.x = bounds.end.x - (size.x) - styleSheet->padding.x;
		break;
	case TextAlignment::Middle_Right:
		textPos.x = bounds.end.x - size.x - styleSheet->padding.x;
		textPos.y = center.y - (size.y / 2.0f);
		break;
	case TextAlignment::Bottom_Right:
		textPos.x = bounds.end.x - size.x - styleSheet->padding.x;
		textPos.y = bounds.end.y - size.y - styleSheet->padding.y;
		break;
	case TextAlignment::Bottom_Middle:
		textPos.x = center.x - (size.x / 2.0f);
		textPos.y = bounds.end.y - size.y - styleSheet->padding.y;
		break;
	case TextAlignment::Bottom_Left:
		textPos.x += styleSheet->padding.x;
		textPos.y = bounds.end.y - size.y - styleSheet->padding.y;
		break;
	case TextAlignment::Middle_Left:
		textPos.x += styleSheet->padding.x;
		textPos.y = center.y - (size.y / 2.0f);
		break;
	case TextAlignment::Middle:
		textPos = center;
		textPos.x -= size.x / 2.0f;
		textPos.y -= size.y / 2.0f;
		break;

	}

	return textPos;
}