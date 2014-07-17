#include "ControlAnimationFloatCurve.h"
#include <Math/Animation/IAnimationCurve.h>

ControlAnimationFloatCurve::ControlAnimationFloatCurve(
	IAnimationCurve* curve,
	float valueBegin,
	float valueEnd,
	float duration) :
	m_curve(curve),
	m_valueBegin(valueBegin),
	m_valueEnd(valueEnd),
	m_duration(duration)
{
}

float ControlAnimationFloatCurve::Evaluate(float time)
{
	return m_curve->Evaluate(m_valueBegin, m_valueEnd, time / m_duration);
}

