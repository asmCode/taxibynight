#ifndef STREET
#define STREET

#include <Math/Matrix.h>
#include <stdint.h>

class Model;
class Texture;
class StreetMap;
class StreetPiece;
class StreetSegment;
class PedsManager;

class Street
{
public:
	static Street *Instance;

	Street(PedsManager *pedsManager);
	~Street();

	void Update(float time, float seconds);
	void Draw(float time, float seconds);

	StreetPiece* GetStreetPiece(uint8_t type);

	void SetTaxiPosition(const sm::Vec3 &taxiPosition);

	void GetSegmentCoords(const sm::Vec3 &position, int32_t &x, int32_t &y) const;
	StreetSegment* GetSegmentAtPosition(const sm::Vec3 &position) const;
	StreetSegment* GetSegment(int x, int y) const;
	void SetInitialVisibility(const sm::Vec3 &taxiPosition);

private:
	static const int Range = 2;

	PedsManager *m_pedsManager;

	sm::Vec3 m_taxiPosition;
	Model *m_streetModel;
	Model *m_skycrapper;

	Texture *m_skycrapperTexture;
	Texture *m_pavementTexture;

	StreetMap *m_streetMap;

	StreetPiece *m_streetPieces[256];

	StreetSegment **m_streetSegments;

	StreetSegment *m_lastTaxiSegment;
};

#endif // STREET

