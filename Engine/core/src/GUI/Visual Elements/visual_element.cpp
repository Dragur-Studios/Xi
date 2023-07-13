#include "visual_element.h"


#include "Util/guid.h"

#include "gui/xss.h"
#include "gui/stylesheet.h"



VisualElement::VisualElement(const std::string& type)
	:  _class{ type }
{
	_guid = Guid::New();
};

VisualElement::VisualElement(const std::string& type, const std::string& name) 
	: _class{ type }, _name{ name } 
{
	_guid = Guid::New();
}

VisualElement::~VisualElement()
{
}

void VisualElement::OnEvent()
{
	ImVec2 mp = ImGui::GetMousePos();
	auto styleSheet = XssEngine::GetStyleSheet(this);
	
	if (styleSheet == nullptr)
		return;
	
	_hover = isWithinBounds(mp, _bounds);
	
	if (!_hover) // cull event calls to any 
		return;

	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && _hover) {
		OnClickCallback();
		_active = true;
	}
	else if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !_hover) {
		_active = false;
	}

}

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
		std::erase(children, element);
	}
}
