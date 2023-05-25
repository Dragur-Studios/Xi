#pragma once

class iApplication
{
public:
	iApplication();
	virtual ~iApplication();

	virtual void OnInitilize() = 0;
	virtual void OnTick() = 0;
	virtual void OnShutdown() = 0;
};


class iGameApplication : public iApplication
{
public:
	iGameApplication();
	virtual ~iGameApplication();

	void Load(class iGame* gamePtr);

	class iGame* game;

};

typedef iApplication* (*XiApplicationFunc)();
typedef iGameApplication* (*XiGameApplicationFunc)();