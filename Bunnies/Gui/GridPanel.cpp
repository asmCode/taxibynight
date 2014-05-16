#include "GridPanel.h"

GridPanel::GridPanel(const std::string &name, Orientation orientation, int gapSize) :
	Control(name),
	m_orientation(orientation),
	m_childrenDistance(gapSize)
{
}

void GridPanel::AddChild(Control *control)
{
	this->Control::AddChild(control);

	Reposition();
}

void GridPanel::RemoveChild(Control *control)
{
	this->Control::RemoveChild(control);

	Reposition();
}

void GridPanel::Reposition()
{
	int base = 0;

	for (int i = 0; i < GetChildrenCount(); i++)
	{
		Control* child = GetChild(i);

		m_orientation == Orientation_Horizontal ?
			child->SetMarginLeft(base) :
			child->SetMarginTop(base);

		base += m_childrenDistance;

		m_orientation == Orientation_Horizontal ?
			base += child->GetWidth() :
			base += child->GetHeight();
	}
}
