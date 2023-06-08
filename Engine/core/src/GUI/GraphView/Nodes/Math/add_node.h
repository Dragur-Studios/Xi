#pragma once


#include "../node.h"

// ADDS TWO INPUTS AND OUTPUTS THE RESULT
struct AddNode :
	public Node
{
public:
	AddNode(float x, float y);
	~AddNode();

	virtual void Create() override;

};


struct SubtractNode :
	public Node
{
public:
	SubtractNode(float x, float y);
	~SubtractNode();

	virtual void Create() override;

};

struct MultiplyNode :
	public Node
{
public:
	MultiplyNode(float x, float y);
	~MultiplyNode();

	virtual void Create() override;

};

struct DivideNode :
	public Node
{
public:
	DivideNode(float x, float y);
	~DivideNode();

	virtual void Create() override;

};