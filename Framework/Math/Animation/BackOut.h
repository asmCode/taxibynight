#pragma once

#include "IAnimationCurve.h"

class BackOut : public IAnimationCurve
{
public:
	float Evaluate(float begin, float end, float time);
};
