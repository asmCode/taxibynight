#include "MathUtils.h"
#include <float.h>

const float MathUtils::PI = 3.141592653589793f;
const float MathUtils::PI2 = 1.57079632679489f;
const float MathUtils::PI4 = 0.78539816339744f;
const float MathUtils::Deg2Rad = 0.0174532925132957f;

void MathUtils::FixToZero(float& v)
{
	if (Abs(v) <= FLT_EPSILON && v != 0.0f)
		v = 0.0f;
}

void MathUtils::FixToZero(sm::Vec3& v)
{
	FixToZero(v.x);
	FixToZero(v.y);
	FixToZero(v.z);
}

float MathUtils::LinearDamp(float start, float end, float change)
{
	float diff = end - start;

	if (Abs(diff) <= Abs(change))
		return 0.0f;

	return start + change * Sign(diff);
}
