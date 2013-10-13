#ifndef PEDS_MANAGER
#define PEDS_MANAGER

#include <Math/Matrix.h>
#include <stdint.h>

class Model;
class Mesh;
class Texture;
class StreetSegment;
class Ped;

class PedsManager
{
public:
	PedsManager(const sm::Vec3 taxiPosition);
	~PedsManager();

	void SetTaxiPosition(const sm::Vec3 &position);
	void Update(float time, float seconds);
	void Draw(float time, float seconds);

	void NotifyStreetSegmentVisibilityChanged(StreetSegment *streetSegment);

private:
	static const uint32_t MaxPeds = 100;
	static const float TaxiViewRange;
	static const uint32_t PassangerPerPeds = 10; // every x ped is a passenger

	Ped *m_peds[MaxPeds];

	uint32_t m_pedResets; /// used to spawn passenger

	sm::Vec3 m_taxiPosition;

	void MovePedNearCar(Ped *ped);
	bool IsOnVisibleSegment(Ped *ped);
	void ResetPosition(Ped *ped, const sm::Vec3 &position, const sm::Vec3 &direction);
};

#endif // PEDS_MANAGER

