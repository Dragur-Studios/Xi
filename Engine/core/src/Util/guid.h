#pragma once

#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>

class Guid {
public:
	static const std::string& New()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 15);

		std::stringstream ss;
		ss << std::hex;

		// Generate random hexadecimal digits for each section of the GUID
		for (int i = 0; i < 8; ++i) {
			ss << dis(gen);
		}

		ss << '-';

		for (int i = 0; i < 4; ++i) {
			ss << dis(gen);
		}

		ss << '-';

		for (int i = 0; i < 4; ++i) {
			ss << dis(gen);
		}

		ss << '-';

		for (int i = 0; i < 4; ++i) {
			ss << dis(gen);
		}

		ss << '-';

		for (int i = 0; i < 12; ++i) {
			ss << dis(gen);
		}

		return ss.str();
	}
};
