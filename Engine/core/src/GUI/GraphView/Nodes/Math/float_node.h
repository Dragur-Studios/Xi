#pragma once

#include "../node.h"

struct FloatNode :
	public Node 
{
	FloatNode(int x, int y);
	~FloatNode();

	virtual void Create() override;


};

struct Float2Node :
	public Node
{
	Float2Node(int x, int y);
	~Float2Node();

	virtual void Create() override;


};

struct Float3Node :
	public Node
{
	Float3Node(int x, int y);
	~Float3Node();

	virtual void Create() override;


};

struct Float4Node :
	public Node
{
	Float4Node(int x, int y);
	~Float4Node();

	virtual void Create() override;


};
