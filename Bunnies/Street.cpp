#include "Street.h"
#include "StreetPiece.h"
#include "StreetSegment.h"
#include "PedsManager.h"
#include "DrawingRoutines.h"
#include "InterfaceProvider.h"
#include "StreetMap.h"
#include "Environment.h"

#include <Utils/Randomizer.h>
#include <Graphics/Model.h>
#include <Graphics/Texture.h>
#include <Math/MathUtils.h>
#include <Graphics/Content/Content.h>
#include <assert.h>

#include <Graphics/OpenglPort.h>

Street *Street::Instance;

Street::Street(PedsManager *pedsManager)
{
	Instance = this;
	m_pedsManager = pedsManager;

	Content *content = InterfaceProvider::GetContent();

	m_streetModel = content->Get<Model>("street");
	assert(m_streetModel != NULL);

	m_skycrapper = content->Get<Model>("skycrapper");
	assert(m_skycrapper != NULL);

	m_skycrapperTexture = content->Get<Texture>("skycrapper");
	assert(m_skycrapperTexture != NULL);

	m_pavementTexture = content->Get<Texture>("street_pavement");
	assert(m_pavementTexture != NULL);

	m_streetMap = new StreetMap(TaxiGame::Environment::GetInstance()->GetBasePath() + "data/");

	m_streetPieces[StreetPiece::PieceType_Pavement] = new StreetPiece(
		StreetPiece::PieceType_Pavement,
		m_streetModel,
		content->Get<Texture>("street_pavement"),
		sm::Matrix::IdentityMatrix());

	m_streetPieces[StreetPiece::PieceType_StraightVert_1] = new StreetPiece(
		StreetPiece::PieceType_StraightVert_1,
		m_streetModel,
		content->Get<Texture>("street_1_straight"),
		sm::Matrix::IdentityMatrix());

	m_streetPieces[StreetPiece::PieceType_StraightHori_1] = new StreetPiece(
		StreetPiece::PieceType_StraightHori_1,
		m_streetModel,
		content->Get<Texture>("street_1_straight"),
		sm::Matrix::RotateAxisMatrix(MathUtils::PI2, 0, 1, 0));

	m_streetPieces[StreetPiece::PieceType_TurnUpRight_1] = new StreetPiece(
		StreetPiece::PieceType_TurnUpRight_1,
		m_streetModel,
		content->Get<Texture>("street_1_turn"),
		sm::Matrix::RotateAxisMatrix(MathUtils::PI2, 0, 1, 0));

	m_streetPieces[StreetPiece::PieceType_TurnUpLeft_1] = new StreetPiece(
		StreetPiece::PieceType_TurnUpLeft_1,
		m_streetModel,
		content->Get<Texture>("street_1_turn"),
		sm::Matrix::RotateAxisMatrix(MathUtils::PI, 0, 1, 0));

	m_streetPieces[StreetPiece::PieceType_TurnDownRight_1] = new StreetPiece(
		StreetPiece::PieceType_TurnDownRight_1,
		m_streetModel,
		content->Get<Texture>("street_1_turn"),
		sm::Matrix::IdentityMatrix());

	m_streetPieces[StreetPiece::PieceType_TurnDownLeft_1] = new StreetPiece(
		StreetPiece::PieceType_TurnDownLeft_1,
		m_streetModel,
		content->Get<Texture>("street_1_turn"),
		sm::Matrix::RotateAxisMatrix(-MathUtils::PI2, 0, 1, 0));

	m_streetPieces[StreetPiece::PieceType_TUp_1] = new StreetPiece(
		StreetPiece::PieceType_TUp_1,
		m_streetModel,
		content->Get<Texture>("street_1_t"),
		sm::Matrix::RotateAxisMatrix(MathUtils::PI, 0, 1, 0));

	m_streetPieces[StreetPiece::PieceType_TDown_1] = new StreetPiece(
		StreetPiece::PieceType_TDown_1,
		m_streetModel,
		content->Get<Texture>("street_1_t"),
		sm::Matrix::ScaleMatrix(1, 1, 1));

	m_streetPieces[StreetPiece::PieceType_TLeft_1] = new StreetPiece(
		StreetPiece::PieceType_TLeft_1,
		m_streetModel,
		content->Get<Texture>("street_1_t"),
		sm::Matrix::RotateAxisMatrix(MathUtils::PI2, 0, 1, 0));

	m_streetPieces[StreetPiece::PieceType_TRight_1] = new StreetPiece(
		StreetPiece::PieceType_TRight_1,
		m_streetModel,
		content->Get<Texture>("street_1_t"),
		sm::Matrix::RotateAxisMatrix(-MathUtils::PI2, 0, 1, 0));

	m_streetPieces[StreetPiece::PieceType_Cross_1] = new StreetPiece(
		StreetPiece::PieceType_Cross_1,
		m_streetModel,
		content->Get<Texture>("street_1_cross"),
		sm::Matrix::IdentityMatrix());

	m_streetPieces[StreetPiece::PieceType_Skycrapper_1] = new StreetPiece(
		StreetPiece::PieceType_Skycrapper_1,
		m_skycrapper,
		m_skycrapperTexture,
		sm::Matrix::IdentityMatrix());

	m_streetSegments = new StreetSegment*[m_streetMap->GetWidth() * m_streetMap->GetHeight()];
	for (uint32_t y = 0; y < m_streetMap->GetHeight(); y++)
	{
		for (uint32_t x = 0; x < m_streetMap->GetWidth(); x++)
		{
			int index = y * m_streetMap->GetWidth() + x;

			StreetPiece::PieceType streetType = m_streetMap->GetPieceType(x, y);
			m_streetSegments[index] = new StreetSegment(sm::Vec3(x * 10.0f, 0, y * 10.0f), m_streetPieces[(uint8_t)streetType]);

			if (m_streetSegments[index]->GetStreetPiece()->HasPavement())
				m_pavementSegments.push_back(m_streetSegments[index]);
		}
	}
}

Street::~Street()
{
}

void Street::Update(float time, float seconds)
{
	StreetSegment *streetSegment = GetSegmentAtPosition(m_taxiPosition);
	if (streetSegment == NULL) // out of map
		return;

	if (streetSegment == m_lastTaxiSegment)
		return;

	int ix = streetSegment->CoordX();
	int iy = streetSegment->CoordY();

	std::vector<StreetSegment*> segmentsChanged;

	for (int y = iy - Range - 1; y <= iy + Range + 1; y++)
	{
		for (int x = ix - Range - 1; x <= ix + Range + 1; x++)
		{
			if (x < 0 || x >= m_streetMap->GetWidth() || y < 0 || y >= m_streetMap->GetHeight())
				continue;

			StreetSegment *ss = GetSegment(x, y);

			if (x < ix - Range ||
				x > ix + Range ||
				y < iy - Range ||
				y > iy + Range)
			{
				if (ss->IsVisible())
				{
					ss->SetVisibility(false);
					segmentsChanged.push_back(ss);
				}
			}
			else
			{
				if (!ss->IsVisible())
				{
					ss->SetVisibility(true);
					segmentsChanged.push_back(ss);
				}
			}
		}
	}

	for (uint32_t i = 0; i < segmentsChanged.size(); i++)
		m_pedsManager->NotifyStreetSegmentVisibilityChanged(segmentsChanged[i]);

	/*if (ix > m_lastTaxiSegment->CoordX() && ix < m_streetMap->GetWidth() - Range)
	{
		StreetSegment *ss;

		ss = GetSegment(ix + Range, iy);
		if (!ss->IsVisible())
		{
			ss->SetVisibility(true);
			m_pedsManager->NotifyStreetSegmentVisibilityChanged(ss);
		}
	}

	m_lastTaxiSegment = streetSegment;*/
}

void Street::Draw(float time, float seconds)
{
	sm::Matrix world = sm::Matrix::IdentityMatrix();

	for (uint32_t y = 0; y < m_streetMap->GetHeight(); y++)
	{
		for (uint32_t x = 0; x < m_streetMap->GetWidth(); x++)
		{
			StreetPiece::PieceType streetType = m_streetMap->GetPieceType(x, y);

			if (!m_streetSegments[y * m_streetMap->GetWidth() + x]->IsVisible())
				continue;

			m_streetPieces[streetType]->Draw(sm::Matrix::TranslateMatrix(x * 10, 0, y * 10));

			/*if (streetType == StreetPiece::PieceType_Skycrapper_1)
				DrawingRoutines::DrawStreet(
					m_streetModel,
					m_pavementTexture,
					sm::Matrix::TranslateMatrix(x * 10, 0, y * 10)
					);*/
		}
	}
}

StreetPiece* Street::GetStreetPiece(uint8_t type)
{
	return m_streetPieces[type];
}

void Street::SetTaxiPosition(const sm::Vec3 &taxiPosition)
{
	m_taxiPosition = taxiPosition;
}

void Street::GetSegmentCoords(const sm::Vec3 &position, int32_t &x, int32_t &y) const
{
	x = (int32_t)((position.x + 5.0f) / 10.0f);
	y = (int32_t)((position.z + 5.0f) / 10.0f);
}

StreetSegment* Street::GetSegmentAtPosition(const sm::Vec3 &position) const
{
	int32_t x;
	int32_t y;
	GetSegmentCoords(position, x, y);

	if (x < 0 || y < 0 || x >= m_streetMap->GetWidth() || y >= m_streetMap->GetHeight())
		return NULL;

	return m_streetSegments[y * m_streetMap->GetWidth() + x];
}

StreetSegment* Street::GetSegment(int x, int y) const
{
	return m_streetSegments[y * m_streetMap->GetWidth() + x];
}

StreetSegment *Street::GetRandomPavement()
{
	static Randomizer random;

	int randomIndex = random.GetInt(0, m_pavementSegments.size() - 1);

	return m_pavementSegments[randomIndex];
}

void Street::SetInitialVisibility(const sm::Vec3 &taxiPosition)
{
	for (uint32_t i = 0; i < m_streetMap->GetWidth() * m_streetMap->GetHeight(); i++)
		m_streetSegments[i]->SetVisibility(false);

	m_lastTaxiSegment = GetSegmentAtPosition(taxiPosition);

	uint32_t ix = m_lastTaxiSegment->CoordX();
	uint32_t iy = m_lastTaxiSegment->CoordY();

	for (int y = MathUtils::Max((int)iy - Range, 0); y <= MathUtils::Min((int)iy + Range, (int)m_streetMap->GetHeight() - 1); y++)
	{
		for (int x = MathUtils::Max((int)ix - Range, 0); x <= MathUtils::Min((int)ix + Range, (int)m_streetMap->GetWidth() - 1); x++)
		{
			m_streetSegments[y * m_streetMap->GetWidth() + x]->SetVisibility(true);
			//m_pedsManager->NotifyStreetSegmentVisibilityChanged(m_streetSegments[y * m_streetMap->GetWidth() + x]);
		}
	}

	for (int y = MathUtils::Max((int)iy - Range, 0); y <= MathUtils::Min((int)iy + Range, (int)m_streetMap->GetHeight() - 1); y++)
	{
		for (int x = MathUtils::Max((int)ix - Range, 0); x <= MathUtils::Min((int)ix + Range, (int)m_streetMap->GetWidth() - 1); x++)
		{
			//m_streetSegments[y * m_streetMap->GetWidth() + x]->SetVisibility(true);
			m_pedsManager->NotifyStreetSegmentVisibilityChanged(m_streetSegments[y * m_streetMap->GetWidth() + x]);
		}
	}
}
