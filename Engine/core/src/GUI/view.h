#pragma once

#include "pch.h"



class View 
{
public:
	View(const std::string& name, const std::string& modelPath, const std::string& stylePath, int flags = 0);
	virtual ~View();

	void Update();
	void Draw();

	void Show();
	void Hide();

	void Compile();
	
public:// interface methods
	virtual void OnCreateGUI() {};
	virtual void OnGUI() { };

protected:
	
	class XDocument* _document;

	bool _compile = true; // compile on the first update always!!
	bool _show; 
	std::string _name;
	int _windowFlags;
	std::string _filepath;
	std::string _styleSheetfilepath;


};