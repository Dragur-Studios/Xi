#pragma once


#include "../node.h"

// ADDS TWO INPUTS AND OUTPUTS THE RESULT
struct AddNode :
	public Node
{
public:
	AddNode(float x, float y);
	~AddNode();

	virtual void OnLink(Pin outputPin, Pin inputPin) override;

	virtual void OnCreateGUI() override;

protected:
	void AddAsFloat();
	void AddAsFloat2();
	void AddAsFloat3();
	void AddAsFloat4();


};


struct SubtractNode :
	public Node
{
public:
	SubtractNode(float x, float y);
	~SubtractNode();

	virtual void OnLink(Pin outputPin, Pin inputPin) override;

	virtual void OnCreateGUI() override;

};

struct MultiplyNode :
	public Node
{
public:
	MultiplyNode(float x, float y);
	~MultiplyNode();
	
	virtual void OnLink(Pin outputPin, Pin inputPin) override;

	virtual void OnCreateGUI() override;

};

struct DivideNode :
	public Node
{
public:
	DivideNode(float x, float y);
	~DivideNode();

	virtual void OnLink(Pin outputPin, Pin inputPin) override;

	virtual void OnCreateGUI() override;

};