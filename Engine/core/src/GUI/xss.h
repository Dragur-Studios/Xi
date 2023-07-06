#pragma once

#include "pch.h"
#include "defs.h"

//void ParseXSS(const std::string& xss, struct StyleSheet* styleSheet);

void ParseSelectorBlocks(const std::string& xss, std::map<std::string, struct StyleSheet*>& styleMap);
