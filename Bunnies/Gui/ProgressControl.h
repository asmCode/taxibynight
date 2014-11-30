#pragma once

#include "../Control.h"
#include <string>

class Label;
class GridPanel;

class ProgressControl : public Control
{
public:
	ProgressControl(
		const std::string& name,
		int maxValue,
		const std::string& atlasName,
		const std::string& activeSpriteName,
		const std::string& inactiveSpriteName);

	void SetTitle(const std::string& title);
	std::string GetTitle() const;

	void SetLimit(int limit);
	void SetValue(int value);
	int GetValue() const;

protected:
	//virtual void OnDraw(float time, float ms);

private:
	std::string m_title;
	int m_maxValues;

	Control *m_view;

	GridPanel* m_cellsGridOn;
	GridPanel* m_cellsGridOff;

	Control **m_fillCells;

	TexPart *m_cellOnTexPart;
	TexPart *m_cellOffTexPart;

	void CreateCells();
};
