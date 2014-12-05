#include "GuiCarUtils.h"
#include "GuiCar.h"
#include "Car.h"
#include "Player.h"
#include "GlobalSettings\GlobalSettings.h"

void GuiCarUtils::LoadPlayerActiveCar(GuiCar* guiCar)
{
	Car* car = Player::Instance->GetActiveCar();
	if (car == NULL)
		return;

	LoadPlayerCar(guiCar, car->GetId());
}

void GuiCarUtils::LoadPlayerCar(GuiCar* guiCar, const std::string& carId)
{
	Car* car = Player::Instance->GetCar(carId);
	if (car == NULL)
		return;

	std::string decalId = car->GetActiveDecalId();
	if (decalId.size() == 0)
		return;

	guiCar->LoadCar(car->GetId());
	guiCar->LoadDecal(decalId);
	guiCar->Show(true);
}

void GuiCarUtils::LoadCarWithDefaultDecal(GuiCar* guiCar, const std::string& carId)
{
	guiCar->LoadCar(carId);
	CarData carData = GlobalSettings::GetCarById(carId);
	if (carData.Decals.size() > 0)
		guiCar->LoadDecal(carData.Decals[0].Id);
	guiCar->Show(true);
}
