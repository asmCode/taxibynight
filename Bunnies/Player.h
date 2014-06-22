#pragma once

#include "CardId.h"
#include <string>
#include <vector>

class PlayerObserver;
class Experience;
class Car;
class XMLNode;

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

	Car* GetActiveCar();
	bool HasCar(const std::string& carId);

private:
	std::string m_path;

	std::string m_activeCarId;
	Car* m_activeCar;
	std::vector<Car*> m_cars;

	Experience* m_experience;
	float m_softMoney;
	float m_hardMoney;

	std::vector<PlayerObserver*> m_observers;

	void NotifyExperienceChanged();
	void NotifyLevelChanged();
	void NotifySoftMoneyChanged();
	void NotifyHardMoneyChanged();

	void LoadCars(XMLNode* node);

	Car* GetCarById(const std::string& id);
};

