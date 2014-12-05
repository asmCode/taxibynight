#pragma once

#include <string>

class GuiCar;

class GuiCarUtils
{
public:
	static void LoadPlayerActiveCar(GuiCar* guiCar);
	static void LoadPlayerCar(GuiCar* guiCar, const std::string& carId);
	static void LoadCarWithDefaultDecal(GuiCar* guiCar, const std::string& carId);
};

