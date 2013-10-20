#include "PedsManager.h"
#include "Ped.h"
#include "DrawingRoutines.h"
#include "InterfaceProvider.h"
#include "Environment.h"
#include "StreetMap.h"
#include "StreetSegment.h"
#include "Street.h"

#include <Graphics/Model.h>
#include <Graphics/Mesh.h>
#include <Graphics/Texture.h>
#include <Utils/Randomizer.h>
#include <Math/MathUtils.h>
#include <Graphics/Content/Content.h>
#include <GL/glew.h>
#include <assert.h>

const float PedsManager::TaxiViewRange = 30.0f;
PedsManager* PedsManager::Instance;

PedsManager::PedsManager(const sm::Vec3 taxiPosition) :
	m_pedApproaching(NULL)
{
	Instance = this;

	m_pedResets = 0;
	m_taxiPosition = taxiPosition;
	Content *content = InterfaceProvider::GetContent();

	for (uint32_t i = 0; i < MaxPeds; i++)
	{
		m_peds[i] = new Ped();
		m_peds[i]->ResetPosition(sm::Vec3(0, 0, 0));
		//MovePedNearCar(m_peds[i]);
	}
}

PedsManager::~PedsManager()
{
}

void PedsManager::SetTaxiPosition(const sm::Vec3 &position)
{
	m_taxiPosition = position;
}

void PedsManager::Update(float time, float seconds)
{
	if (m_pedApproaching != NULL)
	{
		if (!m_pedApproaching->IsTaxiInApproachRange(m_taxiPosition))
		{
			m_pedApproaching->CancelApproach();
			m_pedApproaching = NULL;
		}
		else
			m_pedApproaching->SetTarget(m_taxiPosition);
	}

	for (uint32_t i = 0; i < MaxPeds; i++)
	{
		sm::Vec3 taxiDirection = m_taxiPosition - m_peds[i]->GetPosition();
		float distanceToTaxi = taxiDirection.GetLength();

		if (CanPassangerApproachTocar() && m_peds[i]->IsPassenger() && distanceToTaxi < 5.0f)
		{
			NotifyApproachingToCar(m_peds[i]);
			m_peds[i]->StartApproach();
		}

		m_peds[i]->Update(time, seconds);
	}
}

void PedsManager::Draw(float time, float seconds)
{
	for (uint32_t i = 0; i < MaxPeds; i++)
		m_peds[i]->Draw(time, seconds);
}

//void GetRandomPedPosition(sm::Vec3 &position, sm::Vec3 &direction)
//{
//}

bool PedsManager::IsOnVisibleSegment(Ped *ped)
{
	StreetSegment *ss = Street::Instance->GetSegmentAtPosition(ped->GetPosition());
	return ss->IsVisible();
}

void PedsManager::MovePedNearCar(Ped *ped)
{
	static const int range = 3;

	static Randomizer random;

	int32_t ix;
	int32_t iy;
	Street::Instance->GetSegmentCoords(m_taxiPosition, ix, iy);

	int avaibleSegmentsCount = 0;
	int segmentIndex = 0;

	sm::Vec3 positions[(range * 2 + 1) * (range * 2 + 1)];
	sm::Vec3 directions[(range * 2 + 1) * (range * 2 + 1)];

	for (int32_t y = -range; y <= range; y++)
	{
		for (int32_t x = -range; x <= range; x++)
		{
			if (x != -range && x != range && y != -range && y != range)
				continue;

			sm::Vec3 position;
			sm::Vec3 direction;
			if (StreetMap::Instance->GetRandomPavementArea(ix + x, iy + y, position, direction))
			{
				avaibleSegmentsCount++;

				positions[segmentIndex] = position;
				directions[segmentIndex] = direction;
				segmentIndex++;
			}
		}
	}

	if (avaibleSegmentsCount > 0)
	{
		int randIndex = random.GetInt(0, avaibleSegmentsCount - 1);

		ResetPosition(m_peds[randIndex], positions[randIndex], directions[randIndex]);
	}

	/*sm::Vec3 randomDirection = sm::Vec3(random.GetFloat(-1, 1), 0, random.GetFloat(-1, 1));
	randomDirection.SetLength(random.GetFloat(2, TaxiViewRange));

	sm::Vec3 position = m_taxiPosition + sm::Vec3(randomDirection);
	ped->ResetPosition(position);*/
}

void PedsManager::NotifyStreetSegmentVisibilityChanged(StreetSegment *streetSegment)
{
	if (!streetSegment->GetStreetPiece()->HasPavement())
		return;

	int pedsToSet = 3;

	if (streetSegment->IsVisible())
	{
		int pedIndex = 0;

		while (pedsToSet != 0 || pedIndex == MaxPeds - 1)
		{
			if (!IsOnVisibleSegment(m_peds[pedIndex]))
			{
				sm::Vec3 position;
				sm::Vec3 direction;

				StreetMap::Instance->GetRandomPavementArea(streetSegment->CoordX(), streetSegment->CoordY(), position, direction);
				ResetPosition(m_peds[pedIndex], position, direction);
				pedsToSet--;
			}

			pedIndex++;
		}
	}
}

void PedsManager::ResetPosition(Ped *ped, const sm::Vec3 &position, const sm::Vec3 &direction)
{
	ped->ResetPosition(position);

	m_pedResets++;
	if (m_pedResets == PassangerPerPeds)
	{
		m_pedResets = 0;
		ped->SetToPassenger(sm::Vec3(0, 0, 0), 0.0f);
	}
}

bool PedsManager::CanPassangerApproachTocar() const
{
	return m_pedApproaching == NULL;
}

void PedsManager::NotifyApproachingToCar(Ped *ped)
{
	m_pedApproaching = ped;
}

