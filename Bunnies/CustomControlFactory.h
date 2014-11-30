#pragma once

class ICustomControl;

class CustomControlFactory
{
public:
	virtual ICustomControl* Create() = 0;
};
