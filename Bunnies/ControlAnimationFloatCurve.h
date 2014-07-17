#pragma once

class IAnimationCurve;

class ControlAnimationFloatCurve
{
public:
	ControlAnimationFloatCurve(
		IAnimationCurve* curve,
		float valueBegin,
		float valueEnd,
		float duration);

	virtual ~ControlAnimationFloatCurve() {}

	float Evaluate(float time);

private:
	IAnimationCurve* m_curve;
	float m_valueBegin;
	float m_valueEnd;
	float m_duration;
};

