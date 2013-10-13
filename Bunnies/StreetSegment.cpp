#include "StreetSegment.h"
#include "StreetPiece.h"

#include <Math/MathUtils.h>
#include <assert.h>

StreetSegment::StreetSegment(const sm::Vec3 &pivotPosition, StreetPiece *streetPiece)
{
	m_pivotPosition = pivotPosition;
	m_streetPiece = streetPiece;
}

void StreetSegment::SetVisibility(bool visibility)
{
	m_isVisible = visibility;
}

bool StreetSegment::IsVisible() const
{
	return m_isVisible;
}

StreetPiece *StreetSegment::GetStreetPiece()
{
	return m_streetPiece;
}

uint32_t StreetSegment::CoordX() const
{
	return (uint32_t)((m_pivotPosition.x + 5.0f) / 10.0f);
}

uint32_t StreetSegment::CoordY() const
{
	return (uint32_t)((m_pivotPosition.z + 5.0f) / 10.0f);
}

