#pragma once

#include "IAnimationCurve.h"

class QuarticOut : public IAnimationCurve
{
public:
	float Evaluate(float begin, float end, float time);
};
