#pragma once

#include "../Control.h"

class GridPanel : public Control
{
public:
	enum Orientation
	{
		Orientation_Horizontal,
		Orientation_Vertical
	};

	GridPanel(const std::string& name, Orientation orientation, int gapSize);

	// overrides of Control's methods
	void AddChild(Control *control);
	void RemoveChild(Control *control);

private:
	int m_childrenDistance;
	Orientation m_orientation;
	int m_gapSize;

	void Reposition();
};
