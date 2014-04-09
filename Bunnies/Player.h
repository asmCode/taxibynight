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
	float m_totalMoney;
	float m_bestRoundIncome;
	int m_totalCourses;
	bool m_tutorialFinished;
	bool m_firstRun;

private:
	std::string m_path;
};

