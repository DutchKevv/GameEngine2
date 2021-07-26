#pragma once

class Module
{
public:
	std::string name = "GUI";

	virtual void init()
	{
	}

	virtual void beforeDraw()
	{
	}

	virtual void afterDraw()
	{
	}

	virtual void destroy()
	{
	}
};