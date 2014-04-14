#include "BonusesManager.h"
#include "BonusStreetSymbol.h"
#include "BonusBlowEffect.h"
#include "IBonusesManagerObserver.h"
#include "Bonus.h"
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

#include <UserInput/Input2.h>

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

void BonusesManager::AddObserver(IBonusesManagerObserver* observer)
{
	m_observers.push_back(observer);
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

	UpdateBonuses(seconds);

	if (Input2::GetKeyDown(KeyCode_Num1))
		ActivateBonus(BonusType_Carmageddon);
	if (Input2::GetKeyDown(KeyCode_Num2))
		ActivateBonus(BonusType_Blind);
	if (Input2::GetKeyDown(KeyCode_Num3))
		ActivateBonus(BonusType_PedsAntiMagnet);
	if (Input2::GetKeyDown(KeyCode_Num4))
		ActivateBonus(BonusType_ZombiePeds);
	if (Input2::GetKeyDown(KeyCode_Num5))
		ActivateBonus(BonusType_GenerousClients);
	if (Input2::GetKeyDown(KeyCode_Num6))
		ActivateBonus(BonusType_TakeYourTime);
	if (Input2::GetKeyDown(KeyCode_Num7))
		ActivateBonus(BonusType_FeelThePower);
}

void BonusesManager::Draw(float time, float seconds)
{
	for (uint32_t i = 0; i < MaxBonuses; i++)
	{
		if (m_bonusesSymbols[i]->IsActive())
			m_bonusesSymbols[i]->Draw(time, seconds);
	}

	m_bonusBlowEffect->Draw(time, seconds);

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

		sm::Vec3 bonusPosition = streetSegment->GetPivotPosition();
		static Randomizer random;

		bonusPosition += sm::Vec3(random.GetFloat(-4.5f, 4.5f), 0.0f, random.GetFloat(-4.5f, 4.5f));

		bonus->SetActive(bonusPosition, streetSegment);
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

void BonusesManager::ActivateBonus(BonusType type)
{
	Bonus* bonus = GetActiveBonus(type);
	if (bonus == NULL)
		bonus = new Bonus(type, 10.0f);

	bonus->SetTimeLeft(10.0f);

	m_bonuses[type] = bonus;

	for (uint32_t i = 0; i < m_observers.size(); i++)
		m_observers[i]->BonusActivated(type);
}

float BonusesManager::GetBonusTimeLeft(BonusType type)
{
	return 12.47f;
}

Bonus* BonusesManager::GetActiveBonus(BonusType type)
{
	std::map<BonusType, Bonus*>::iterator it = m_bonuses.find(type);
	if (it == m_bonuses.end())
		return NULL;

	return it->second;
}

void BonusesManager::UpdateBonuses(float seconds)
{
	std::map<BonusType, Bonus*>::iterator it;
	std::vector<Bonus*> bonusesToDelete;

	for (it = m_bonuses.begin(); it != m_bonuses.end(); it++)
	{
		it->second->DecreaseTimeLeft(seconds);

		if (it->second->IsRunDown())
			bonusesToDelete.push_back(it->second);
	}

	for (uint32_t i = 0; i < bonusesToDelete.size(); i++)
	{
		for (uint32_t j = 0; j < m_observers.size(); j++)
			m_observers[j]->BonusDeactivated(bonusesToDelete[i]->GetBonusType());

		m_bonuses.erase(bonusesToDelete[i]->GetBonusType());
		delete bonusesToDelete[i];
	}
}

