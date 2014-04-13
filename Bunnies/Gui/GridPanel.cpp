#include "GridPanel.h"

GridPanel::GridPanel(const std::string &name) :
	Control(name),
	m_childrenDistance(8)
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
	int baseY = 0;

	for (int i = 0; i < GetChildrenCount(); i++)
	{
		Control* child = GetChild(i);
		child->SetMarginTop(baseY);

		baseY += child->GetHeight() + m_childrenDistance;
	}
}
