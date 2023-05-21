#pragma once

class iApplication
{

public:
	iApplication();
	virtual ~iApplication();

	virtual void OnInitilize() = 0;
	virtual void OnTick() = 0;
	virtual void OnShutdown() = 0;

	void Load(class iGame*);

protected:
	class iGame* game;

};

typedef iApplication* (*XiApplication)();