#include "TrafficManager.h"
#include "Car.h"
#include "DrawingRoutines.h"
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

	m_cars[0]->SetActive(Taxi::GetInstance()->GetPosition());

	return true;
}

void TrafficManager::Update(float time, float seconds)
{
	for (int i = 0; i < MaxCars; i++)
	{
		if (!m_cars[i]->IsActive())
			continue;

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
