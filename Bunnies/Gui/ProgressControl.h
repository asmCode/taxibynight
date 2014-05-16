#pragma once

#include "../Control.h"
#include <string>

class Label;
class GridPanel;

class ProgressControl : public Control
{
public:
	ProgressControl(const std::string& name, int maxValue);

	void SetName(const std::string& name);
	std::string GetName() const;

	void SetValue(int value);
	int GetValue() const;

protected:
	//virtual void OnDraw(float time, float ms);

private:
	std::string m_name;
	int m_maxValues;

	Control *m_view;

	Label* m_nameLabel;
	GridPanel* m_cellsGridOn;
	GridPanel* m_cellsGridOff;

	Control **m_fillCells;

	void CreateCells();
};
