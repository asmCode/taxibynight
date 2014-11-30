#include "Player.h"
#include "PlayerObserver.h"
#include "Car.h"
#include "DecalId.h"
#include "Experience.h"
#include "GlobalSettings/GlobalSettings.h"
#include <Utils/StringUtils.h>
#include <IO/Path.h>
#include <XML/XMLLoader.h>
#include <XML/XMLNode.h>
#include <string>

Player *Player::Instance;

Player::Player(const std::string &path) :
	m_id(""),
	m_name("unnamed"),
	m_softMoney(0.0f),
	m_hardMoney(0.0f),
	m_totalCourses(0),
	m_bestRoundIncome(0.0f),
	m_tutorialFinished(false),
	m_firstRun(true),
	m_activeCar(NULL),
	m_activeCarId(""),
	m_path(path)
{
	m_experience = new Experience(0);

	Instance = this;
}

void Player::Load()
{
	if (!Path::IsFileExists(m_path.c_str()))
		return;

	XMLNode *node = XMLLoader::LoadFromFile(m_path);
	if (node == NULL)
		return;

	for (uint32_t i = 0; i < node->GetChildrenCount(); i++)
	{
		XMLNode *child = node->GetChild(i);
		if (child->GetName() == "Experience")
			m_experience->SetExperienceValue(child->GetValueAsFloat());
		else if (child->GetName() == "ActiveCar")
			m_activeCarId = child->GetValueAsString();
		else if (child->GetName() == "SoftMoney")
			m_softMoney = child->GetValueAsFloat();
		else if (child->GetName() == "HardMoney")
			m_hardMoney = child->GetValueAsFloat();
		else if (child->GetName() == "TotalCourses")
			m_totalCourses = child->GetValueAsInt32();
		else if (child->GetName() == "BestRoundIncome")
			m_bestRoundIncome = child->GetValueAsFloat();
		else if (child->GetName() == "TutorialFinished")
			m_tutorialFinished = child->GetValueAsBool();
		else if (child->GetName() == "FirstRun")
			m_firstRun = child->GetValueAsBool();
		else if (child->GetName() == "Id")
			m_id = child->GetValueAsString();
		else if (child->GetName() == "Name")
			m_name = StringUtils::FromBase64(child->GetValueAsString());
	}

	LoadCars(node);

	if (m_activeCarId.length() > 0)
		ActicateCar(m_activeCarId);
}

void Player::Save()
{
	std::string xml;

	xml += "<Player>\n";
	xml += "\t<Id>"; xml += m_id; xml += "</Id>\n";
	xml += "\t<Name>"; xml += StringUtils::ToBase64(m_name); xml += "</Name>\n";
	xml += "\t<Experience>"; xml += StringUtils::ToString(m_experience->GetExperienceValue()); xml += "</Experience>\n";
	xml += "\t<SoftMoney>"; xml += StringUtils::ToString(m_softMoney); xml += "</SoftMoney>\n";
	xml += "\t<HardMoney>"; xml += StringUtils::ToString(m_hardMoney); xml += "</HardMoney>\n";
	xml += "\t<TotalCourses>"; xml += StringUtils::ToString(m_totalCourses); xml += "</TotalCourses>\n";
	xml += "\t<BestRoundIncome>"; xml += StringUtils::ToString(m_bestRoundIncome); xml += "</BestRoundIncome>\n";
	xml += "\t<TutorialFinished>"; xml += m_tutorialFinished ? "true" : "false"; xml += "</TutorialFinished>\n";
	xml += "\t<FirstRun>"; xml += m_firstRun ? "true" : "false"; xml += "</FirstRun>\n";
	xml += "\t<ActiveCar>"; xml += m_activeCarId + "</ActiveCar>\n";
	xml += SaveCars("\t");
	xml += "</Player>\n";

	Path::WriteTextFile(m_path.c_str(), xml);
}

void Player::Reset()
{
	SetSoftMoney(0.0f);
	SetHardMoney(0.0f);
	SetExperience(0.0f);
	m_totalCourses = 0;
	m_bestRoundIncome = 0;
	m_tutorialFinished = false;
	m_firstRun = true;
	m_activeCar = NULL;
	m_activeCarId = "";

	m_cars.clear();
}

float Player::GetExperience() const
{
	return m_experience->GetExperienceValue();
}

int Player::GetLevel() const
{
	return m_experience->GetLevel();
}

float Player::GetSoftMoney() const
{
	return m_softMoney;
}

float Player::GetHardMoney() const
{
	return m_hardMoney;
}

void Player::SetExperience(float experience)
{
	assert(experience >= 0);

	if (m_experience->GetExperienceValue() != experience)
	{
		int prevLevel = GetLevel();

		m_experience->SetExperienceValue(experience);

		Save();

		NotifyExperienceChanged();

		if (GetLevel() != prevLevel)
			NotifyLevelChanged();
	}
}

void Player::SetSoftMoney(float softMoney)
{
	assert(softMoney >= 0);

	if (m_softMoney != softMoney)
	{
		m_softMoney = softMoney;

		Save();

		NotifySoftMoneyChanged();
	}
}

void Player::SetHardMoney(float hardMoney)
{
	assert(hardMoney >= 0);

	if (m_hardMoney != hardMoney)
	{
		m_hardMoney = hardMoney;

		Save();

		NotifyHardMoneyChanged();
	}
}

void Player::AddObserver(PlayerObserver *observer)
{
	m_observers.push_back(observer);
}

Car* Player::GetActiveCar()
{
	return m_activeCar;
}

Car* Player::GetCar(const std::string& id)
{
	for (uint32_t i = 0; i < m_cars.size(); i++)
	if (m_cars[i]->GetId() == id)
		return m_cars[i];

	return NULL;
}

void Player::AddCar(const std::string& carId)
{
	assert(HasCar(carId) == false);
	if (HasCar(carId))
		return;

	CarData carData = GlobalSettings::GetCarById(carId);

	Car* car = new Car(carData, 0, 0, 0, std::vector<DecalData>());
	car->SetDefaultDecal();
	m_cars.push_back(car);

	car->AddObserver(this);

	Save();
}

void Player::ActicateCar(const std::string& carId)
{
	assert(HasCar(carId));
	if (!HasCar(carId))
		return;

	m_activeCarId = carId;
	m_activeCar = GetCar(m_activeCarId);

	Save();
}

bool Player::HasCar(const std::string& carId)
{
	return GetCar(carId) != NULL;
}

std::string Player::SaveCars(const std::string& tab)
{
	std::string xml;
	
	xml += tab + "<Cars>\n";

	for (uint32_t i = 0; i < m_cars.size(); i++)
		xml += SaveCar(m_cars[i], tab + "\t");

	xml += tab + "</Cars>\n";

	return xml;
}

std::string Player::SaveCar(Car* car, const std::string& tab)
{
	std::string xml;

	xml += tab + "<Car ";
	xml += "id=\"" + car->GetId() + "\" ";
	xml += "speed_level=\"" + StringUtils::ToString(car->GetUpgradeLevel(UpgradeId::Speed)) + "\" ";
	xml += "acc_level=\"" + StringUtils::ToString(car->GetUpgradeLevel(UpgradeId::Acc)) + "\" ";
	xml += "tires_level=\"" + StringUtils::ToString(car->GetUpgradeLevel(UpgradeId::Tires)) + "\" ";
	xml += SaveDecals(car);
	xml += "/>\n";

	return xml;
}

std::string Player::SaveDecals(Car* car)
{
	const std::vector<DecalData>& decals = car->GetDecals();
	if (decals.size() == 0)
		return "";

	std::string xml = "decals=\"";
	
	for (uint32_t i = 0; i < decals.size(); i++)
	{
		xml += decals[i].Id;
		if (i < decals.size() - 1)
			xml += ",";
	}

	xml += "\" ";
	xml += "active_decal=\"" + car->GetActiveDecalId() + "\" ";

	return xml;
}

void Player::NotifyExperienceChanged()
{
	for (uint32_t i = 0; i < m_observers.size(); i++)
		m_observers[i]->ExperienceChanged();
}

void Player::NotifyLevelChanged()
{
	for (uint32_t i = 0; i < m_observers.size(); i++)
		m_observers[i]->LevelChanged();
}

void Player::NotifySoftMoneyChanged()
{
	for (uint32_t i = 0; i < m_observers.size(); i++)
		m_observers[i]->SoftMoneyChanged();
}

void Player::NotifyHardMoneyChanged()
{
	for (uint32_t i = 0; i < m_observers.size(); i++)
		m_observers[i]->HardMoneyChanged();
}

void Player::LoadCars(XMLNode* node)
{
	XMLNode* carsNode = node->GetChild("Cars");
	if (carsNode == NULL)
		return;

	for (uint32_t i = 0; i < carsNode->GetChildrenCount(); i++)
	{
		XMLNode* carNode = carsNode->GetChild(i);

		std::string id = carNode->GetAttribAsString("id");
		int speedLevel = carNode->GetAttribAsInt32("speed_level");
		int accLevel = carNode->GetAttribAsInt32("acc_level");
		int tiresLevel = carNode->GetAttribAsInt32("tires_level");
		std::string activeDecal = carNode->GetAttribAsString("active_decal");

		CarData carData = GlobalSettings::GetCarById(id);

		assert(speedLevel <= carData.GetUpgradeSlotsCount(UpgradeId::Speed));
		assert(accLevel <= carData.GetUpgradeSlotsCount(UpgradeId::Acc));
		assert(tiresLevel <= carData.GetUpgradeSlotsCount(UpgradeId::Tires));

		std::string decalsString = carNode->GetAttribAsString("decals");
		std::vector<DecalData> decals;

		if (decalsString.size() > 0)
		{
			std::vector<std::string> decalsIds;
			StringUtils::Split(decalsString, ",", decalsIds);

			for (uint32_t decalIndex = 0; decalIndex < decalsIds.size(); decalIndex++)
				decals.push_back(carData.GetDecalData(decalsIds[decalIndex]));
		}

		Car* car = new Car(
			carData,
			speedLevel,
			accLevel,
			tiresLevel,
			decals);

		car->SetDecal(activeDecal);

		m_cars.push_back(car);

		car->AddObserver(this);
	}
}

void Player::AddedDecal(Car* car, const std::string& decalId)
{
	Save();
}

void Player::ChangedDecal(Car* car, const std::string& decalId)
{
	Save();
}
