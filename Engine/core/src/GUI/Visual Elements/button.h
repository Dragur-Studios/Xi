#pragma once

#include "visual_element.h"
#include "util/guid.h"
#include <functional>

constexpr float def_Width = 100.0f;
constexpr float def_Height = 30.0f;

template<typename T>
class Action {

public:
	void operator()() {
		for (const auto fn : _data)
		{
			fn();
		}
	}

	void operator +=(std::function<T> other) {
		_data.push_back(other);
	}

	void operator-=(std::function<T> other) {
		_data.erase(other);
	}

private:
	std::vector<std::function<T>> _data;
};


class Button : public VisualElement
{
public:
	using OnClick = Action<void()>;


public:
	Button(const std::string& label);
	
	~Button();

	virtual void OnCreateGUI() override;
	virtual void OnClickCallback() override;

	std::string _label;

	OnClick clicked;

};