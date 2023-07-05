#pragma once

#include "GUI/view.h"
#include <sstream>

class ImGuiStreamInterceptor : public std::streambuf {
public:
	ImGuiStreamInterceptor(std::ostream& stream) 
		: stream{ stream }
	{
		backup = stream.rdbuf();
		stream.rdbuf(this);
	}

	~ImGuiStreamInterceptor()
	{
		stream.rdbuf(backup);
	}

	void ClearLogs() {
		logs.clear();
	}

	size_t LogCount() {
		return logs.size();
	}

	 const std::string& GetLog(int pos) const {
		return logs[pos];
	}

protected:
	int_type overflow(int_type ch) {
		if (ch != EOF) {
			buffer += static_cast<char>(ch);
			if (ch == '\n') {
				logs.push_back(buffer);
				buffer.clear();
			}
		}
		return ch;
	}



private:
	std::ostream& stream;
	std::streambuf* backup;
	std::string buffer;

	std::vector<std::string> logs;
};


class Terminal : public View
{
public:
	Terminal();
	~Terminal();

	//virtual void Update() override;
	//virtual void HandleContextMenu() override;


private:
	ImGuiStreamInterceptor* stdInterceptor;
};

