#include "button.h"

#include "gui/stylesheet.h"

Button::Button(const std::string& label, OnClick clickfn)
	: _label{ label }, _onclick{ clickfn }
{};
Button::~Button() 
{};

void Button::Render(ImRect bounds)
{
	ImVec2 mp = ImGui::GetMousePos();

	hover = isWithinBounds(mp, bounds);

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	drawList->Flags = ImDrawListFlags_::ImDrawListFlags_AntiAliasedFill;

	ImColor background = hover ? styleSheet->background_color.hover : styleSheet->background_color.normal;
	ImColor font = hover ? styleSheet->font_color.hover : styleSheet->font_color.normal;

	// draw the containing rectangle. this will contain the border, padding and content size.
	drawList->AddRectFilled(bounds.start, bounds.end, background, styleSheet->rounding);

	if (ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Left) && hover) {
		_onclick();
	}

	drawList->AddText(AlignText(bounds, _label.c_str(), styleSheet->text_align), font, _label.c_str());

}