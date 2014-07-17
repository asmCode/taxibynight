#pragma once

#include <Math\Vec4.h>

class IAnimationCurve;

class ControlAnimationVector4Curve
{
public:
	ControlAnimationVector4Curve(
		IAnimationCurve* curve,
		const sm::Vec4& valueBegin,
		const sm::Vec4& valueEnd,
		float duration);

	virtual ~ControlAnimationVector4Curve() {}

	sm::Vec4 Evaluate(float time);

private:
	IAnimationCurve* m_curve;
	sm::Vec4 m_valueBegin;
	sm::Vec4 m_valueEnd;
	float m_duration;
};

