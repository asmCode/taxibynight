#include "ControlAnimation.h"
#include "ControlAnimationTarget.h"
#include "ControlAnimationFloatCurve.h"
#include "ControlAnimationVector4Curve.h"
#include "Control.h"
#include <Math/Animation/LinearCurve.h>
#include <Utils/StringUtils.h>
#include <XML/XMLLoader.h>
#include <XML/XMLNode.h>
#include <assert.h>

ControlAnimation::ControlAnimation() :
	m_time(0.0f)
{

}

ControlAnimation* ControlAnimation::LoadFromFile(const std::string& filename)
{
	XMLNode* root = XMLLoader::LoadFromFile(filename);
	if (root == NULL)
		return NULL;

	if (root->GetName() != "Animation")
		return NULL;

	ControlAnimation* anim = new ControlAnimation();

	for (uint32_t i = 0; i < root->GetChildrenCount(); i++)
	{
		XMLNode* node = root->GetChild(0);
		assert(node != NULL);

		ControlAnimationTarget* target = LoadTarget(node);
		assert(target != NULL);

		anim->m_targets.push_back(target);
	}

	return anim;
}

void ControlAnimation::SetTarget(Control* control)
{
	assert(control != NULL);

	for (uint32_t i = 0; i < m_targets.size(); i++)
	{
		Control* child = control->FindChild(m_targets[i]->GetTargetName());
		assert(child != NULL);

		m_targets[i]->SetTarget(child);
	}
}

float ControlAnimation::GetTime() const
{
	return m_time;
}

void ControlAnimation::SetTime(float time)
{
	m_time = time;

	for (uint32_t i = 0; i < m_targets.size(); i++)
		m_targets[i]->SetAnimationTime(m_time);
}

void ControlAnimation::Update(float deltaTime)
{
	SetTime(m_time + deltaTime);
}

ControlAnimationTarget* ControlAnimation::LoadTarget(XMLNode* node)
{
	assert(node != NULL);
	assert(node->GetName() == "Target");

	std::string targetName = node->GetAttribAsString("name");
	assert(targetName.size() > 0);
	ControlAnimationVector4Curve* transformCurve = NULL;
	ControlAnimationFloatCurve* rotateCurve = NULL;
	ControlAnimationFloatCurve* scaleCurve = NULL;
	ControlAnimationVector4Curve* colorCurve = NULL;

	XMLNode* transformNode = node->GetChild("Transform");
	if (transformNode != NULL)
	{
		sm::Vec4 valueBegin;
		sm::Vec4 valueEnd;
		IAnimationCurve* curve;
		float duration;

		LoadCurve(transformNode, valueBegin, valueEnd, curve, duration);

		transformCurve = new ControlAnimationVector4Curve(curve, valueBegin, valueEnd, duration);
	}

	ControlAnimationTarget* target = new ControlAnimationTarget(
		targetName,
		transformCurve,
		rotateCurve,
		scaleCurve,
		colorCurve);

	return target;
}

void ControlAnimation::LoadCurve(
	XMLNode* node,
	sm::Vec4& valueBegin,
	sm::Vec4& valueEnd,
	IAnimationCurve*& curve,
	float& duration)
{
	std::string fromVal = node->GetAttribAsString("from");
	assert(fromVal.size() > 0);
	std::string toVal = node->GetAttribAsString("to");
	assert(toVal.size() > 0);
	std::string curveTxt = node->GetAttribAsString("curve", "linear");
	duration = node->GetAttribAsFloat("duration");

	std::vector<std::string> fromComponents;
	StringUtils::Split(fromVal, ";", fromComponents);
	std::vector<std::string> toComponents;
	StringUtils::Split(toVal, ";", toComponents);

	assert(fromComponents.size() == toComponents.size());

	for (uint32_t i = 0; i < fromComponents.size(); i++)
	{
		sscanf(fromComponents[i].c_str(), "%f", &valueBegin[i]);
		sscanf(toComponents[i].c_str(), "%f", &valueEnd[i]);
	}

	if (curveTxt == "linear")
		curve = new LinearCurve();
}
