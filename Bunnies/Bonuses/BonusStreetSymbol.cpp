#include "BonusStreetSymbol.h"
#include "../InterfaceProvider.h"
#include "../DrawingRoutines.h"
#include <Graphics/Model.h>
#include <Graphics/Content/Content.h>
#include <assert.h>

Model* BonusStreetSymbol::m_model;

void BonusStreetSymbol::Initialize()
{
	Content *content = InterfaceProvider::GetContent();

	m_model = content->Get<Model>("bonus");
	assert(m_model != NULL);
}

BonusStreetSymbol::BonusStreetSymbol() :
	m_position(0, 0, 0),
	m_angle(0.0f),
	m_height(0.0f)
{
}

BonusStreetSymbol::~BonusStreetSymbol()
{
}

void BonusStreetSymbol::SetPosition(const sm::Vec3& position)
{
	m_position = position;
}

void BonusStreetSymbol::Update(float time, float seconds)
{
	m_angle += seconds * 3.0f;
	m_height = (sinf(time * 10.1f)  + 1.0f) * 0.5f;

	m_transform =
		sm::Matrix::TranslateMatrix(m_position + sm::Vec3(0, m_height, 0)) *
		sm::Matrix::RotateAxisMatrix(m_angle, 0, 1, 0);
}

void BonusStreetSymbol::Draw(float time, float seconds)
{
	DrawingRoutines::DrawWithMaterial(m_model->m_meshParts, m_transform);
}

void BonusStreetSymbol::DrawShadow(float time, float seconds)
{

}
