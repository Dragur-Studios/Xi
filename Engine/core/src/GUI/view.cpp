#include "view.h"

#include "imgui/imgui.h"

#include "XDocument/xdocument.h"

View::View(const std::string& name, const std::string& modelPath, const std::string& stylePath, int flags)
	: _show{ true }, _name{ name }, _windowFlags{ flags }, _styleSheetfilepath{stylePath}, _filepath{modelPath}
{ 	
	_document = new XDocument(_filepath, _styleSheetfilepath);
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
	_document->Compile();
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
			OnGUI();

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
