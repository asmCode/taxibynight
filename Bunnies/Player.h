#pragma once

#include <string>

class Player
{
public:
	static Player *Instance;

	Player(const std::string &path);

	void Load();
	void Save();

	float m_totalMoney;
	float m_bestRoundIncome;
	int m_totalCourses;

private:
	std::string m_path;
};

