#include "ProgressControl.h"
#include "../Label.h"
#include "GridPanel.h"
#include "../Inflater.h"
#include "../Environment.h"
#include "../Atlas.h"
#include "../InterfaceProvider.h"
#include "../SpritesMap.h"
#include <Graphics/SpriteBatch.h>
#include <Utils/StringUtils.h>

ProgressControl::ProgressControl(
	const std::string& name,
	int maxValues,
	const std::string& atlasName,
	const std::string& activeSpriteName,
	const std::string& inactiveSpriteName) :
	Control(name),
	m_maxValues(maxValues),
	m_fillCells(NULL),
	m_cellOnTexPart(NULL),
	m_cellOffTexPart(NULL)
{
	m_view = Inflater::Inflate(TaxiGame::Environment::GetInstance()->GetBasePath() + "data/gui/ProgressControl.xml");

	//SetWidth(m_view->GetWidth());
	//SetHeight(m_view->GetHeight());

	this->AddChild(m_view);

	m_cellsGridOn = dynamic_cast<GridPanel*>(m_view->FindChild("cells_grid_on"));
	m_cellsGridOff = dynamic_cast<GridPanel*>(m_view->FindChild("cells_grid_off"));

	if (atlasName.size() > 0)
	{
		m_cellOnTexPart = InterfaceProvider::m_atlases[atlasName]->GetTexPart(activeSpriteName);
		m_cellOffTexPart = InterfaceProvider::m_atlases[atlasName]->GetTexPart(inactiveSpriteName);
	}

	assert(m_cellsGridOn != NULL);
	assert(m_cellsGridOff != NULL);

	CreateCells();
}

std::string ProgressControl::GetTitle() const
{
	return m_name;
}

void ProgressControl::SetLimit(int limit)
{
	m_maxValues = limit;

	CreateCells();
}

void ProgressControl::SetValue(int value)
{
	for (int i = 0; i < m_maxValues; i++)
	{
		m_fillCells[i]->SetVisible(value > i);
	}
}

int ProgressControl::GetValue() const
{
	return 0;
}

void ProgressControl::CreateCells()
{
	if (m_fillCells != NULL)
	{
		delete[] m_fillCells;

		while (m_cellsGridOff->GetChildrenCount() > 0)
			m_cellsGridOff->RemoveChild(m_cellsGridOff->GetChild(0));

		while (m_cellsGridOn->GetChildrenCount() > 0)
			m_cellsGridOn->RemoveChild(m_cellsGridOn->GetChild(0));
	}

	m_fillCells = new Control*[m_maxValues];

	if (m_cellOffTexPart != NULL)
	{
		for (int i = 0; i < m_maxValues; i++)
		{
			Control *cell = new Control("", 0, 0, *m_cellOffTexPart);
			cell->SetAlign("top-left");
			m_cellsGridOff->AddChild(cell);
		}
	}

	if (m_cellOnTexPart != NULL)
	{
		for (int i = 0; i < m_maxValues; i++)
		{
			Control *cell = new Control("", 0, 0, *m_cellOnTexPart);
			cell->SetVisible(false);
			cell->SetAlign("top-left");
			m_cellsGridOn->AddChild(cell);
			m_fillCells[i] = cell;
		}
	}
}
