#include "TextField.h"

#include "Util/guid.h"
#include "gui/stylesheet.h"
#include <GUI/xss.h>

TextField::TextField()
    : VisualElement("textfield")
{
}

TextField::~TextField()
{
}

void TextField::OnCreateGUI()
{ 
    auto drawList = ImGui::GetWindowDrawList();
    auto styleSheet = XssEngine::GetStyleSheet(this);
    
    const ImFont* font = ImGui::GetIO().Fonts->Fonts[0];

    auto rounding = (SingleValueProperty<float>*)styleSheet->properties["rounding"];
	auto background_color = (SingleValueProperty<ImColorState>*) styleSheet->properties["background-color"];
	auto font_color = (SingleValueProperty<ImColorState>*) styleSheet->properties["font-color"];
	auto border_color = (SingleValueProperty<ImColorState>*) styleSheet->properties["border-color"];

	ImColor _background =
		_hover ?
		background_color->value.hover :
		_active ?
		background_color->value.active :
		background_color->value.normal;

	ImColor _font = _hover ?
		font_color->value.hover :
		_active ?
		font_color->value.active :
		font_color->value.normal;

	ImColor _border =
		_hover ?
		border_color->value.hover :
		_active ?
		border_color->value.active :
		border_color->value.normal;

    drawList->AddRectFilled(_bounds.start, _bounds.end, _background, rounding->value, ImDrawListFlags_AntiAliasedFill | ImDrawListFlags_AntiAliasedLines);
    drawList->AddText(font, 16.0f, _bounds.start, _font, "Some Text Goes Here");
 
}
