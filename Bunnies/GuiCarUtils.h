#pragma once

#include <string>

class GuiCar;

class GuiCarUtils
{
public:
	static void LoadPlayerCar(GuiCar* guiCar);
	static void LoadCarWithDefaultDecal(GuiCar* guiCar, const std::string& carId);
};

