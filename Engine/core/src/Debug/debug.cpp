#include "debug.h"

#include "windows.h"

void Debug::Log(const std::string& message, LogSeverity severity) {
	
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	if (console == INVALID_HANDLE_VALUE) {
		std::cerr << "Faild To Obtain Handle" << std::endl;
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO info{};
	GetConsoleScreenBufferInfo(console, &info);

	WORD last_color = info.wAttributes;

	switch (severity)
	{
	case Debug::Info:
		SetConsoleTextAttribute(console, (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE));
		break;
	case Debug::Success:
		SetConsoleTextAttribute(console, FOREGROUND_GREEN);
		std::cout << "\t";
		break;
	case Debug::Warning:
		SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED);
		std::cout << "\t";
		break;
	case Debug::Error:
		SetConsoleTextAttribute(console, FOREGROUND_RED);
		std::cout << "\t";
		break;
	case Debug::Fatal:
		std::cout << "\t";
		SetConsoleTextAttribute(console, BACKGROUND_RED | (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE));
		break;
	}

	std::cout << message << std::endl;
	
	SetConsoleTextAttribute(console, last_color);

}