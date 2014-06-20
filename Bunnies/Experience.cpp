#include "Experience.h"
#include <assert.h>

Experience::Experience(float experienceValue) :
	m_experienceValue(experienceValue)
{
}

float Experience::GetExperienceValue() const
{
	return m_experienceValue;
}

int Experience::GetLevel() const
{
	return GetLevelForExperienceValue(m_experienceValue);
}

void Experience::SetExperienceValue(float experience)
{
	m_experienceValue = experience;
}

float Experience::GetExperienceValueForLevel(int level)
{
	assert(level > 0);

	return 100.0f * (level - 1);
}

int Experience::GetLevelForExperienceValue(float experienceValue)
{
	return static_cast<int>(experienceValue / 100.0f) + 1;
}
