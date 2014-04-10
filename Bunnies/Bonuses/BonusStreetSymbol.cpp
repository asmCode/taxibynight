#include "BonusStreetSymbol.h"
#include "../InterfaceProvider.h"
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

BonusStreetSymbol::BonusStreetSymbol()
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

}

void BonusStreetSymbol::Draw(float time, float seconds)
{

}

void BonusStreetSymbol::DrawShadow(float time, float seconds)
{

}
