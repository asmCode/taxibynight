#pragma once

#include <string>

class Player
{
public:
	static Player *Instance;

	Player(const std::string &path);

	void Load();
	void Save();

	std::string m_id;
	std::string m_name;
	float m_bestRoundIncome;
	int m_totalCourses;
	bool m_tutorialFinished;
	bool m_firstRun;

	float GetExperience() const;
	float GetSoftMoney() const;
	float GetHardMoney() const;

	void SetExperience(float experience);
	void SetSoftMoney(float softMoney);
	void SetHardMoney(float hardMoney);

private:
	std::string m_path;

	float m_experience;
	float m_softMoney;
	float m_hardMoney;
};

