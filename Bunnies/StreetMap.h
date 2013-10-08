#ifndef STREET_MAP
#define STREET_MAP

#include <Math/Matrix.h>
#include <string>
#include <stdint.h>

class StreetMap
{
public:
	enum StreetType : uint8_t
	{
		StreetType_Pavement = 0,
		StreetType_StraightHori_1,
		StreetType_StraightVert_1,
		StreetType_TurnUpRight_1,
		StreetType_TurnUpLeft_1,
		StreetType_TurnDownRight_1,
		StreetType_TurnDownLeft_1,
		StreetType_Cross_1,
		StreetType_TUp_1,
		StreetType_TDown_1,
		StreetType_TLeft_1,
		StreetType_TRight_1,

		StreetType_Skycrapper_1,
	};

	enum PixelType : uint8_t
	{
		PixelType_Green,
		PixelType_Red,
		PixelType_Blue,
		PixelType_White,
	};

	StreetMap(const std::string &dataPath);
	~StreetMap();

	uint32_t GetWidth() const;
	uint32_t GetHeight() const;

	StreetType GetStreetType(uint32_t x, uint32_t y) const;

private:
	uint8_t *m_streetMap;

	uint32_t m_width;
	uint32_t m_height;

	PixelType GetPixelType(uint8_t *data, uint32_t x, uint32_t y);
};

#endif // STREET_MAP

