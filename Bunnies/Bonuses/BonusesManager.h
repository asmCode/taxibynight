#ifndef BONUSES_MANAGER
#define BONUSES_MANAGER

#include <Math/Matrix.h>
#include <Core/stdint.h>

class Model;
class Mesh;
class Texture;
class StreetSegment;
class Ped;
class BonusStreetSymbol;
class BonusBlowEffect;

class BonusesManager
{
public:
	static BonusesManager *Instance;

	void Reset(const sm::Vec3 &taxiPosition);

	BonusesManager();
	~BonusesManager();

	void SetViewProjMatrix(const sm::Matrix& viewProjMatrix);
	void SetTaxiPosition(const sm::Vec3 &position);
	void Update(float time, float seconds);
	void Draw(float time, float seconds);

	void NotifyStreetSegmentVisibilityChanged(StreetSegment *streetSegment);

private:
	static const uint32_t MaxBonuses = 10;
	static const float TaxiViewRange;

	BonusStreetSymbol *m_bonusesSymbols[MaxBonuses];

	BonusBlowEffect* m_bonusBlowEffect;

	sm::Vec3 m_taxiPosition;
	sm::Matrix m_viewProjMatrix;

	void MovePedNearCar(Ped *ped);
	bool IsOnVisibleSegment(Ped *ped);
	void ResetPosition(Ped *ped, const sm::Vec3 &position, const sm::Vec3 &direction);

	void OnBonusCollected(BonusStreetSymbol* bonusStreetSymbol);

	BonusStreetSymbol* GetInactiveBonusSymbol();
};

#endif // BONUSES_MANAGER

