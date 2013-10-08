#include "StreetMap.h"
#include "InterfaceProvider.h"

#include <Graphics/Content/Content.h>
#include <Graphics/ImageLoader.h>
#include <assert.h>

StreetMap::StreetMap(const std::string &dataPath)
{
	uint8_t *data;
	uint32_t bytesCount;

	if (!ImageLoader::LoadFromFile(dataPath + "Textures/street_map.png", data, m_width, m_height, bytesCount))
	{
		assert(false);
		return;
	}

	m_streetMap = new uint8_t[m_width * m_height];
	memset(m_streetMap, 0, m_width * m_height);

	for (uint32_t y = 1; y < m_height - 1; y++)
	{
		for (uint32_t x = 1; x < m_width - 1; x++)
		{
			PixelType pixelType = GetPixelType(data, x, y);
			PixelType pLeft = GetPixelType(data, x - 1, y);
			PixelType pRight = GetPixelType(data, x + 1, y);
			PixelType pUp = GetPixelType(data, x, y + 1);
			PixelType pDown = GetPixelType(data, x, y - 1);

			if (pixelType == PixelType_White)
				m_streetMap[y * m_width + x] = StreetType_Pavement;
			else if ( // prosto poziomo
				pixelType == PixelType_Green &&
				pLeft == PixelType_Green &&
				pRight == PixelType_Green &&
				pUp!= PixelType_Green &&
				pDown != PixelType_Green)
				m_streetMap[y * m_width + x] = StreetType_StraightHori_1;
			else if ( // prosto pionowo
				pixelType == PixelType_Green &&
				pLeft != PixelType_Green &&
				pRight != PixelType_Green &&
				pUp == PixelType_Green &&
				pDown == PixelType_Green)
				m_streetMap[y * m_width + x] = StreetType_StraightVert_1;
			else if ( // skret up prawo
				pixelType == PixelType_Green &&
				pLeft != PixelType_Green &&
				pRight == PixelType_Green &&
				pUp != PixelType_Green &&
				pDown == PixelType_Green)
				m_streetMap[y * m_width + x] = StreetType_TurnUpRight_1;
			else if ( // skret up lewo
				pixelType == PixelType_Green &&
				pLeft == PixelType_Green &&
				pRight != PixelType_Green &&
				pUp != PixelType_Green &&
				pDown == PixelType_Green)
				m_streetMap[y * m_width + x] = StreetType_TurnUpLeft_1;
			else if ( // skret down prawo
				pixelType == PixelType_Green &&
				pLeft != PixelType_Green &&
				pRight == PixelType_Green &&
				pUp == PixelType_Green &&
				pDown != PixelType_Green)
				m_streetMap[y * m_width + x] = StreetType_TurnDownRight_1;
			else if ( // skret down lewo
				pixelType == PixelType_Green &&
				pLeft == PixelType_Green &&
				pRight != PixelType_Green &&
				pUp == PixelType_Green &&
				pDown != PixelType_Green)
				m_streetMap[y * m_width + x] = StreetType_TurnDownLeft_1;
			else if ( // up T
				pixelType == PixelType_Green &&
				pLeft == PixelType_Green &&
				pRight == PixelType_Green &&
				pUp == PixelType_Green &&
				pDown != PixelType_Green)
				m_streetMap[y * m_width + x] = StreetType_TUp_1;
			else if ( // down T
				pixelType == PixelType_Green &&
				pLeft == PixelType_Green &&
				pRight == PixelType_Green &&
				pUp != PixelType_Green &&
				pDown == PixelType_Green)
				m_streetMap[y * m_width + x] = StreetType_TDown_1;
			else if ( // left T
				pixelType == PixelType_Green &&
				pLeft == PixelType_Green &&
				pRight != PixelType_Green &&
				pUp == PixelType_Green &&
				pDown == PixelType_Green)
				m_streetMap[y * m_width + x] = StreetType_TLeft_1;
			else if ( // Right T
				pixelType == PixelType_Green &&
				pLeft != PixelType_Green &&
				pRight == PixelType_Green &&
				pUp == PixelType_Green &&
				pDown == PixelType_Green)
				m_streetMap[y * m_width + x] = StreetType_TRight_1;
			else if ( // cross
				pixelType == PixelType_Green &&
				pLeft == PixelType_Green &&
				pRight == PixelType_Green &&
				pUp == PixelType_Green &&
				pDown == PixelType_Green)
				m_streetMap[y * m_width + x] = StreetType_Cross_1;

			else if ( // skycrapper
				pixelType == PixelType_Blue)
				m_streetMap[y * m_width + x] = StreetType_Skycrapper_1;
		}
	}

	delete [] data;
}

StreetMap::~StreetMap()
{
	delete [] m_streetMap;
}

uint32_t StreetMap::GetWidth() const
{
	return m_width;
}

uint32_t StreetMap::GetHeight() const
{
	return m_height;
}

StreetMap::StreetType StreetMap::GetStreetType(uint32_t x, uint32_t y) const
{
	return (StreetMap::StreetType)m_streetMap[y * m_width + x];
}

StreetMap::PixelType StreetMap::GetPixelType(uint8_t *data, uint32_t x, uint32_t y)
{
	uint8_t r = *(data + ((y * m_width + x) * 4) + 0);
	uint8_t g = *(data + ((y * m_width + x) * 4) + 1);
	uint8_t b = *(data + ((y * m_width + x) * 4) + 2);

	if (r > 240 && g == 0 && b == 0)
		return PixelType_Red;
	if (r == 0 && g > 240 && b == 0)
		return PixelType_Green;
	if (r == 0 && g == 0 && b > 240)
		return PixelType_Blue;
	if (r > 240 && g > 240 && b > 240)
		return PixelType_White;

	assert(false);
	return PixelType_White;
}

