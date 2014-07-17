#pragma once

#include <Math/Vec4.h>
#include <string>
#include <vector>

class Control;
class ControlAnimationTarget;
class XMLNode;
class IAnimationCurve;

class ControlAnimation
{
public:
	virtual ~ControlAnimation() {};

	static ControlAnimation* LoadFromFile(const std::string& filename);

	void SetTarget(Control* control);

	float GetTime() const;
	void SetTime(float time);

	void Update(float deltaTime);

private:
	ControlAnimation();

	std::vector<ControlAnimationTarget*> m_targets;

	float m_time;

	static ControlAnimationTarget* LoadTarget(XMLNode* node);
	static void LoadCurve(
		XMLNode* node,
		sm::Vec4& valueBegin,
		sm::Vec4& valueEnd,
		IAnimationCurve*& curve,
		float& duration);
};

