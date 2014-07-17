#include "ControlAnimationVector4Curve.h"
#include <Math/Animation/IAnimationCurve.h>

ControlAnimationVector4Curve::ControlAnimationVector4Curve(
	IAnimationCurve* curve,
	const sm::Vec4& valueBegin,
	const sm::Vec4& valueEnd,
	float duration) :
	m_curve(curve),
	m_valueBegin(valueBegin),
	m_valueEnd(valueEnd),
	m_duration(duration)
{
}

sm::Vec4 ControlAnimationVector4Curve::Evaluate(float time)
{
	return sm::Vec4(
		m_curve->Evaluate(m_valueBegin.x, m_valueEnd.x, time / m_duration),
		m_curve->Evaluate(m_valueBegin.y, m_valueEnd.y, time / m_duration),
		m_curve->Evaluate(m_valueBegin.w, m_valueEnd.z, time / m_duration),
		m_curve->Evaluate(m_valueBegin.x, m_valueEnd.w, time / m_duration));
}

