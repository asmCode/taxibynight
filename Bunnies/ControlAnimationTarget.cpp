#pragma once

#include "ControlAnimationTarget.h"
#include "ControlAnimationFloatCurve.h"
#include "ControlAnimationVector4Curve.h"
#include "Control.h"
#include <assert.h>

ControlAnimationTarget::ControlAnimationTarget(
	const std::string& targetName,
	ControlAnimationVector4Curve* transformCurve,
	ControlAnimationFloatCurve* rotationCurve,
	ControlAnimationFloatCurve* scaleCurve,
	ControlAnimationVector4Curve* colorCurve) :
	m_targetName(targetName),
	m_control(NULL),
	m_transformCurve(transformCurve),
	m_rotationCurve(rotationCurve),
	m_scaleCurve(scaleCurve),
	m_colorCurve(colorCurve)
{
}

void ControlAnimationTarget::SetTarget(Control* control)
{
	m_control = control;
}

void ControlAnimationTarget::SetAnimationTime(float time)
{
	assert(m_control != NULL);

	if (m_transformCurve != NULL)
		m_control->m_animTransform = m_transformCurve->Evaluate(time);
	if (m_rotationCurve != NULL)
		m_control->m_animRotate = m_rotationCurve->Evaluate(time);
	if (m_scaleCurve != NULL)
		m_control->m_animScale = m_scaleCurve->Evaluate(time);
	if (m_colorCurve != NULL)
		m_control->m_animColor = m_colorCurve->Evaluate(time);
}

const std::string& ControlAnimationTarget::GetTargetName() const
{
	return m_targetName;
}
