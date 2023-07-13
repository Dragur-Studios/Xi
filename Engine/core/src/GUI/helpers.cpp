#include "helpers.h"

#include "Visual Elements/visual_element.h"
#include "stylesheet.h"

#include "xss.h"

ImVec2 AlignText(VisualElement* element, const std::string& text, int alignment)
{
	ImTextAlignment align = (ImTextAlignment)alignment;
	auto bounds = element->_bounds;

	auto textPos = bounds.start;

	auto size = ImGui::CalcTextSize(text.c_str());
	auto center = ImVec2((bounds.end.x + bounds.start.x) / 2.0f, (bounds.end.y + bounds.start.y) / 2.0f);

	auto styleSheet = XssEngine::GetStyleSheet(element);

	auto padding = (MultiValueProperty<float, 4>*)styleSheet->properties["padding"];

	switch (align)
	{
	case ImTextAlignment::Top_Left:
		textPos.x += padding->value[0];
		textPos.y += padding->value[1];
		break;
	case ImTextAlignment::Top_Middle:
		textPos.y += padding->value[1];
		textPos.x = center.x - (size.x / 2.0f);
		break;
	case ImTextAlignment::Top_Right:
		textPos.y += padding->value[1];
		textPos.x = bounds.end.x - (size.x) - padding->value[0];
		break;
	case ImTextAlignment::Center_Right:
		textPos.x = bounds.end.x - size.x - padding->value[0];
		textPos.y = center.y - (size.y / 2.0f);
		break;
	case ImTextAlignment::Bottom_Right:
		textPos.x = bounds.end.x - size.x - padding->value[0];
		textPos.y = bounds.end.y - size.y - padding->value[1];
		break;
	case ImTextAlignment::Bottom_Middle:
		textPos.x = center.x - (size.x / 2.0f);
		textPos.y = bounds.end.y - size.y - padding->value[1];
		break;
	case ImTextAlignment::Bottom_Left:
		textPos.x += padding->value[0];
		textPos.y = bounds.end.y - size.y - padding->value[1];
		break;
	case ImTextAlignment::Center_Left:
		textPos.x += padding->value[0];
		textPos.y = center.y - (size.y / 2.0f);
		break;
	case ImTextAlignment::Center:
		textPos = center;
		textPos.x -= size.x / 2.0f;
		textPos.y -= size.y / 2.0f;
		break;

	}

	return textPos;
}

