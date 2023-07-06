#include "label.h"
#include "gui/stylesheet.h"

Label::Label(const std::string& text)
	: _text{ text }
{
	styleSheet->width = -1;
	styleSheet->height = 30.0f;
	styleSheet->padding = { 5, 5, 5, 5 };
}

Label::~Label()
{
}

void Label::Render(ImRect bounds)
{
	styleSheet->width = ImGui::GetContentRegionMax().x;

	ImDrawList* drawList = ImGui::GetWindowDrawList();


	/// TEMP  
	{
		drawList->Flags = ImDrawListFlags_::ImDrawListFlags_AntiAliasedFill;

		ImColor background = hover ? styleSheet->background_color.hover : styleSheet->background_color.normal;
		ImColor font = hover ? styleSheet->font_color.hover : styleSheet->font_color.normal;

		// draw the containing rectangle. this will contain the border, padding and content size.
		drawList->AddRectFilled(bounds.start, bounds.end, background, styleSheet->rounding);

	}

	drawList->AddText(AlignText(bounds, _text.c_str(), styleSheet->text_align), styleSheet->font_color.normal, _text.c_str());

}