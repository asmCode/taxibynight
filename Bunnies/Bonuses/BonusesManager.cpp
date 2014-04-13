#include "BonusesManager.h"
#include "BonusStreetSymbol.h"
#include "BonusBlowEffect.h"
#include "../Environment.h"
#include "../StreetMap.h"
#include "../StreetSegment.h"
#include "../Street.h"
#include "../GameScreen.h"

#include <Graphics/Model.h>
#include <Graphics/Mesh.h>
#include <Graphics/Texture.h>
#include <Utils/Randomizer.h>
#include <Math/MathUtils.h>
#include <Graphics/Content/Content.h>
#include <Audio/SoundManager.h>
#include <assert.h>

#include <Graphics/OpenglPort.h>

const float BonusesManager::TaxiViewRange = 30.0f;
BonusesManager* BonusesManager::Instance;

BonusesManager::BonusesManager()
{
	Instance = this;

	for (uint32_t i = 0; i < MaxBonuses; i++)
		m_bonusesSymbols[i] = new BonusStreetSymbol();

	m_bonusBlowEffect = new BonusBlowEffect();
}

void BonusesManager::Reset(const sm::Vec3 &taxiPosition)
{
}

BonusesManager::~BonusesManager()
{
}

void BonusesManager::SetTaxiPosition(const sm::Vec3 &position)
{
	m_taxiPosition = position;
}

void BonusesManager::Update(float time, float seconds)
{
	m_bonusBlowEffect->Update(time, seconds, m_viewProjMatrix);

	for (uint32_t i = 0; i < MaxBonuses; i++)
	{
		if (!m_bonusesSymbols[i]->IsActive())
			continue;

		sm::Vec3 taxiDirection = m_taxiPosition - m_bonusesSymbols[i]->GetPosition();
		float distanceToTaxi = taxiDirection.GetLength();

		if (distanceToTaxi < 3.0f)
		{
			OnBonusCollected(m_bonusesSymbols[i]);
			continue;
		}

		m_bonusesSymbols[i]->Update(time, seconds);
	}
}

void BonusesManager::Draw(float time, float seconds)
{
	for (uint32_t i = 0; i < MaxBonuses; i++)
	{
		if (m_bonusesSymbols[i]->IsActive())
			m_bonusesSymbols[i]->Draw(time, seconds);
	}

	/*
	DrawingRoutines::DrawUnlitBegin(m_peds[0]->m_shadow->m_meshParts[0]);
	for (uint32_t i = 0; i < MaxPeds; i++)
	{
		if (IsOnVisibleSegment(m_peds[i]) && !m_peds[i]->m_isDying)
			m_peds[i]->DrawShadow(time, seconds);
	}
	DrawingRoutines::DrawUnlitEnd();
	*/
}

void BonusesManager::NotifyStreetSegmentVisibilityChanged(StreetSegment *streetSegment)
{
	if (!streetSegment->GetStreetPiece()->IsStreet())
		return;

	if (!streetSegment->IsVisible())
	{
		for (uint32_t i = 0; i < MaxBonuses; i++)
			if (m_bonusesSymbols[i]->GetStreetSegment() == streetSegment)
				m_bonusesSymbols[i]->SetInactive();
	}

	if (streetSegment->IsVisible())
	{
		BonusStreetSymbol *bonus = GetInactiveBonusSymbol();
		if (bonus == NULL)
			return;

		bonus->SetActive(streetSegment->GetPivotPosition(), streetSegment);
	}
}

void BonusesManager::OnBonusCollected(BonusStreetSymbol* bonusStreetSymbol)
{
	m_bonusBlowEffect->SetPosition(bonusStreetSymbol->GetPosition());
	m_bonusBlowEffect->Blow();

	bonusStreetSymbol->SetInactive();
}

BonusStreetSymbol* BonusesManager::GetInactiveBonusSymbol()
{
	for (uint32_t i = 0; i < MaxBonuses; i++)
		if (!m_bonusesSymbols[i]->IsActive())
			return m_bonusesSymbols[i];

	return NULL;
}

void BonusesManager::SetViewProjMatrix(const sm::Matrix& viewProjMatrix)
{
	m_viewProjMatrix = viewProjMatrix;
}
