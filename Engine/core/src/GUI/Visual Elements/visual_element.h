#pragma once
#include "pch.h"
#include "defs.h"

#include "visual_element.h"

#include "imgui/imgui.h"


struct VisualElement {
	std::string guid;
	ImVec2 position;
	ImVec2 size;

	std::vector<VisualElement*> children;

	void Add(VisualElement* element) {
		children.push_back(element);
	}

	void Remove(VisualElement* element) {
		auto it = std::find(children.begin(), children.end(), element);
		if (it != children.end()) {
			std::remove(children.begin(), children.end(), element);
		}
	}

	template<typename T>
	T Q(std::string name="") {
		
		for (auto& child : children)
		{
			bool override = name.empty();

			if (typeid(child) == typeid(T) && (child.id == name || override)) {
				return child;
			}

		}

		return {};
	}
};