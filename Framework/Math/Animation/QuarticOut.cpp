#include "QuarticOut.h"
#include "../MathUtils.h"

float QuarticOut::Evaluate(float begin, float end, float time)
{
	time = MathUtils::Clamp(time, 0.0f, 1.0f);

	float c = end - begin;
	time--;
	return -c * (time*time*time*time - 1) + begin;
};
