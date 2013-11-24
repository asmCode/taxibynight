#include "TrafficManager.h"
#include "Car.h"
#include "DrawingRoutines.h"
#include "StreetSegment.h"
#include "StreetPiece.h"
#include "Street.h"
#include "InterfaceProvider.h"
#include "Taxi.h"
#include <Graphics/Model.h>
#include <Graphics/Content/Content.h>

TrafficManager::TrafficManager()
{
}

TrafficManager::~TrafficManager()
{
	for (int i = 0; i < MaxCars; i++)
		delete m_cars[i];
}

bool TrafficManager::Initialize()
{
	for (int i = 0; i < MaxCars; i++)
	{
		m_cars[i] = new Car();
	}

	Content *content = InterfaceProvider::GetContent();

	m_carModel = content->Get<Model>("car01");
	assert(m_carModel != NULL);

	return true;
}

void TrafficManager::Update(float time, float seconds)
{
	for (int i = 0; i < MaxCars; i++)
	{
		if (!m_cars[i]->IsActive())
			continue;

		if (m_cars[i]->IsActive() && !IsOnVisibleSegment(m_cars[i]))
		{
			m_cars[i]->SetInactive();
			break;
		}

		m_cars[i]->Update(time, seconds);
	}
}

void TrafficManager::Draw(float time, float seconds)
{
	for (int i = 0; i < MaxCars; i++)
	{
		if (!m_cars[i]->IsActive())
			continue;

		DrawingRoutines::DrawWithMaterial(m_carModel->m_meshParts, m_cars[i]->GetWorldMatrix());
	}
}

void TrafficManager::NotifyStreetSegmentVisibilityChanged(StreetSegment *streetSegment)
{
	if (!streetSegment->GetStreetPiece()->HasRoad())
		return;

	// CHANGE
	int carsToSet = 1;

	if (streetSegment->IsVisible())
	{
		int carIndex = 0;
		
		while (carsToSet != 0 && carIndex <= MaxCars - 1)
		{
			if (!m_cars[carIndex]->IsActive())
			{
				m_cars[carIndex]->SetActive(streetSegment->GetPivotPosition());

				carsToSet--;
			}

			carIndex++;
		}
	}
}

bool TrafficManager::IsOnVisibleSegment(Car *car)
{
	StreetSegment *ss = Street::Instance->GetSegmentAtPosition(car->GetPosition());
	if (ss != NULL)
		return ss->IsVisible();

	return false;
}

