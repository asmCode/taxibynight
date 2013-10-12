#include "Street.h"
#include "DrawingRoutines.h"
#include "InterfaceProvider.h"
#include "StreetMap.h"
#include "Environment.h"

#include <Graphics/Model.h>
#include <Graphics/Texture.h>
#include <Math/MathUtils.h>
#include <Graphics/Content/Content.h>
#include <GL/glew.h>
#include <assert.h>

Street::Street()
{
	Content *content = InterfaceProvider::GetContent();

	m_streetModel = content->Get<Model>("street");
	assert(m_streetModel != NULL);

	m_skycrapper = content->Get<Model>("skycrapper");
	assert(m_skycrapper != NULL);

	m_skycrapperTexture = content->Get<Texture>("skycrapper");
	assert(m_skycrapperTexture != NULL);

	m_pavementTexture = content->Get<Texture>("street_pavement");
	assert(m_pavementTexture != NULL);

	m_streetMap = new StreetMap(Environment::GetInstance()->GetBasePath() + "/Data/");

	m_streetPieces[StreetMap::StreetType_Pavement].Set(m_streetModel, content->Get<Texture>("street_pavement"), sm::Matrix::IdentityMatrix());
	m_streetPieces[StreetMap::StreetType_StraightVert_1].Set(m_streetModel, content->Get<Texture>("street_1_straight"), sm::Matrix::IdentityMatrix());
	m_streetPieces[StreetMap::StreetType_StraightHori_1].Set(m_streetModel, content->Get<Texture>("street_1_straight"), sm::Matrix::RotateAxisMatrix(MathUtils::PI2, 0, 1, 0));
	m_streetPieces[StreetMap::StreetType_TurnUpRight_1].Set(m_streetModel, content->Get<Texture>("street_1_turn"), sm::Matrix::RotateAxisMatrix(MathUtils::PI2, 0, 1, 0));
	m_streetPieces[StreetMap::StreetType_TurnUpLeft_1].Set(m_streetModel, content->Get<Texture>("street_1_turn"), sm::Matrix::RotateAxisMatrix(MathUtils::PI, 0, 1, 0));
	m_streetPieces[StreetMap::StreetType_TurnDownRight_1].Set(m_streetModel, content->Get<Texture>("street_1_turn"), sm::Matrix::IdentityMatrix());
	m_streetPieces[StreetMap::StreetType_TurnDownLeft_1].Set(m_streetModel, content->Get<Texture>("street_1_turn"), sm::Matrix::RotateAxisMatrix(-MathUtils::PI2, 0, 1, 0));
	m_streetPieces[StreetMap::StreetType_TUp_1].Set(m_streetModel, content->Get<Texture>("street_1_t"), sm::Matrix::RotateAxisMatrix(MathUtils::PI, 0, 1, 0));
	m_streetPieces[StreetMap::StreetType_TDown_1].Set(m_streetModel, content->Get<Texture>("street_1_t"), sm::Matrix::ScaleMatrix(1, 1, 1));
	m_streetPieces[StreetMap::StreetType_TLeft_1].Set(m_streetModel, content->Get<Texture>("street_1_t"), sm::Matrix::RotateAxisMatrix(MathUtils::PI2, 0, 1, 0));
	m_streetPieces[StreetMap::StreetType_TRight_1].Set(m_streetModel, content->Get<Texture>("street_1_t"), sm::Matrix::RotateAxisMatrix(-MathUtils::PI2, 0, 1, 0));
	m_streetPieces[StreetMap::StreetType_Cross_1].Set(m_streetModel, content->Get<Texture>("street_1_cross"), sm::Matrix::IdentityMatrix());

	m_streetPieces[StreetMap::StreetType_Skycrapper_1].Set(m_skycrapper, m_skycrapperTexture, sm::Matrix::IdentityMatrix());
}

Street::~Street()
{
}

void Street::Update(float time, float seconds)
{
}

void Street::Draw(float time, float seconds)
{
	sm::Matrix world = sm::Matrix::IdentityMatrix();

	for (uint32_t y = 0; y < m_streetMap->GetHeight(); y++)
	{
		for (uint32_t x = 0; x < m_streetMap->GetWidth(); x++)
		{
			StreetMap::StreetType streetType = m_streetMap->GetStreetType(x, y);

			DrawingRoutines::DrawStreet(
				m_streetPieces[streetType].m_model,
				m_streetPieces[streetType].m_texture,
				sm::Matrix::TranslateMatrix(x * 10, 0, y * 10) * m_streetPieces[streetType].m_world);

			if (streetType == StreetMap::StreetType_Skycrapper_1)
				DrawingRoutines::DrawStreet(
					m_streetModel,
					m_pavementTexture,
					sm::Matrix::TranslateMatrix(x * 10, 0, y * 10)
					);
		}
	}
}
