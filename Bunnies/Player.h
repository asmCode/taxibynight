#pragma once

#include <string>
#include <vector>

class PlayerObserver;

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
	int GetLevel() const;
	float GetSoftMoney() const;
	float GetHardMoney() const;

	void SetExperience(float experience);
	void SetSoftMoney(float softMoney);
	void SetHardMoney(float hardMoney);

	void AddObserver(PlayerObserver *observer);

private:
	std::string m_path;

	float m_experience;
	float m_softMoney;
	float m_hardMoney;

	std::vector<PlayerObserver*> m_observers;

	void NotifyExperienceChanged();
	void NotifyLevelChanged();
	void NotifySoftMoneyChanged();
	void NotifyHardMoneyChanged();
};

