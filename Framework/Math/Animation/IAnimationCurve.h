#pragma once

class IAnimationCurve
{
public:
	virtual ~IAnimationCurve() {};

	virtual float Evaluate(float begin, float end, float time) = 0;
};
