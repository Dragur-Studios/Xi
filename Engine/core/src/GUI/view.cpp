#include "view.h"

#include "imgui/imgui.h"

#include "XDocument/xdocument.h"

View::View(const std::string& name, int flags)
	: _show{ true }, _name{ name }, _windowFlags{ flags }
{ 	
	_document = new XDocument();
}

View::~View()
{
}

void View::Update()
{
	_document->Update();
}

void View::Compile() {
	_compile = true;
}

void View::Draw() 
{
	if (_show)
	{
		if (!ImGui::Begin(_name.c_str(), &_show, (ImGuiWindowFlags)_windowFlags)) {
			ImGui::End();
		}
		else 
		{
			_document->Draw();
			ImGui::End();
		}
	}
}

void View::Show()
{
	_show = true;
}

void View::Hide()
{
	_show = false;
}
