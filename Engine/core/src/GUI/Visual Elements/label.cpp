#include "label.h"
#include "gui/stylesheet.h"
#include "gui/helpers.h"
#include <GUI/xss.h>

Label::Label(const std::string& text)
	: VisualElement("label"), _text{text}
{

}

Label::~Label()
{
}

void Label::OnCreateGUI()
{
	ImDrawList* drawList = ImGui::GetWindowDrawList();

	auto styleSheet = XssEngine::GetStyleSheet(this);
	auto width = (SingleValueProperty<float>*)styleSheet->properties["width"];
	auto text_align = (SingleValueProperty<TextAlignment>*)styleSheet->properties["text-align"];
	auto font_color = (SingleValueProperty<ImColorState>*)styleSheet->properties["color"];
	
	drawList->AddText(AlignText(this, _text.c_str(), text_align->value), font_color->value.normal, _text.c_str());

}