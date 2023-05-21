#pragma once

#include <iostream>

namespace Debug {
	enum LogSeverity {
		Info,
		Success,
		Warning,
		Error,
		Fatal,
	};

	void Log(const std::string& message, LogSeverity severity=LogSeverity::Info);
}

#define LOG_INFO(msg) Debug::Log(msg, Debug::LogSeverity::Info);
#define LOG_SUCCESS(msg) Debug::Log(msg, Debug::LogSeverity::Success);
#define LOG_WARNING(msg) Debug::Log(msg, Debug::LogSeverity::Warning);
#define LOG_ERROR(msg) Debug::Log(msg, Debug::LogSeverity::Error);
#define LOG_Fatal(msg) Debug::Log(msg, Debug::LogSeverity::Fatal);
