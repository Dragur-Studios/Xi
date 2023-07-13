#include "button.h"

#include "gui/stylesheet.h"
#include "gui/helpers.h"
#include <GUI/xss.h>

Button::Button(const std::string& label, OnClick clickfn)
	: VisualElement("button"), _label { label }, _onclick{std::move(clickfn)}
{};

Button::Button(const std::string& label, const std::string& name, OnClick clickfn) : VisualElement("button", name), _label{ label }, _onclick{ clickfn}{

}

Button::~Button() 
{};

void Button::OnCreateGUI()
{
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	drawList->Flags = ImDrawListFlags_::ImDrawListFlags_AntiAliasedFill;
	

	auto styleSheet = XssEngine::GetStyleSheet(this);
	auto rounding = (SingleValueProperty<float>*)styleSheet->properties["rounding"];
	auto text_align = (SingleValueProperty<TextAlignment>*)styleSheet->properties["text-align"];
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
	
	drawList->AddRectFilled(_bounds.start, _bounds.end, _background, rounding->value);
	drawList->AddText(AlignText(this, _label.c_str(), text_align->value), _font, _label.c_str());

}

void Button::OnClickCallback()
{
	_onclick();
}
