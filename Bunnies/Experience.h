#pragma once

class Experience
{
public:
	Experience(float experienceValue);

	float GetExperienceValue() const;
	int GetLevel() const;

	void SetExperienceValue(float experience);

	static float GetExperienceValueForLevel(int level);
	static int GetLevelForExperienceValue(float experienceValue);

private:
	float m_experienceValue;
};

