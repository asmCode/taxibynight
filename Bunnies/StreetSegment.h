#ifndef STREET_SEGMENT
#define STREET_SEGMENT

#include <Math/Matrix.h>
#include <Core/stdint.h>

class StreetPiece;

class StreetSegment
{
public:
	StreetSegment(const sm::Vec3 &pivotPosition, StreetPiece *streetPiece);

	void SetVisibility(bool visibility);

	bool IsVisible() const;
	StreetPiece *GetStreetPiece();

	uint32_t CoordX() const;
	uint32_t CoordY() const;

private:
	StreetPiece *m_streetPiece;
	sm::Vec3 m_pivotPosition;
	bool m_isVisible;
};

#endif // STREET_SEGMENT
