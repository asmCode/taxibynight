#pragma once

#include <string>

class ControlAnimationFloatCurve;
class ControlAnimationVector4Curve;
class Control;

class ControlAnimationTarget
{
public:
	ControlAnimationTarget(
		const std::string& targetName,
		ControlAnimationVector4Curve* transformCurve,
		ControlAnimationFloatCurve* rotationCurve,
		ControlAnimationFloatCurve* scaleCurve,
		ControlAnimationVector4Curve* colorCurve);

	virtual ~ControlAnimationTarget() {};

	void SetTarget(Control* control);
	void SetAnimationTime(float time);

	const std::string& GetTargetName() const;

private:
	std::string m_targetName;
	Control* m_control;
	ControlAnimationVector4Curve* m_transformCurve;
	ControlAnimationFloatCurve* m_rotationCurve;
	ControlAnimationFloatCurve* m_scaleCurve;
	ControlAnimationVector4Curve* m_colorCurve;
};

