#pragma once

#include "../Control.h"

class GridPanel : public Control
{
public:
	GridPanel(const std::string& name);

	// overrides of Control's methods
	void AddChild(Control *control);
	void RemoveChild(Control *control);

private:
	int m_childrenDistance;

	void Reposition();
};
