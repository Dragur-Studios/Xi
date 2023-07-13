#pragma once

#include "pch.h"
#include "defs.h"

class XssEngine {
public:
	static void Compile(const std::string& filepath, struct ImVec2 windowSize);

	static class StyleSheet* GetStyleSheet(class VisualElement* element);

private:
	static class StyleSheet* GetClass(const std::string& className);
	static class StyleSheet* GetID(const std::string& id);
	static class StyleSheet* GetName(const std::string& name);
	static void UpdateNameVars(const std::string selector, StyleSheet& sheet);
	static void UpdateIDVars(const std::string selector, StyleSheet& sheet);

	static void Parse(const std::string& xss, struct ImVec2 windowSize);
	static void ParseStyleProperty(const std::string& property, const std::string& value, class StyleSheet& styleSheet, struct ImVec2 windowSize);

	static std::map<std::string, class StyleSheet*> styleMap;

};
