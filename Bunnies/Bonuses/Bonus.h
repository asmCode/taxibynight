#ifndef BONUS
#define BONUS

#include <Math/Matrix.h>
#include <Core/stdint.h>

class BonusStreetSymbol;

class Bonus
{
public:
	Bonus();
	~Bonus();

	bool IsActive() const;

private:
	bool m_isActive;
};

#endif // BONUS

