#pragma once

#include "IAnimationCurve.h"

class LinearCurve : public IAnimationCurve
{
public:
	float Evaluate(float begin, float end, float time);
};
