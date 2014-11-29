#pragma once

#include "Point.h"
#include "FontLetter.h"
#include <Math/Matrix.h>
#include <string>
#include "Color.h"

class SpriteBatch;

class FontRenderer
{
private:
	FontLetter texLetters[256];
	SpriteBatch *m_spriteBatch;
	
	FontRenderer();
	static bool ParseBounds(const std::string &strBounds, sm::Rect<int> &bounds);
	static Texture *LoadFontBitmap(const std::string &path);
	
public:
	static FontRenderer* LoadFromFile(const char *path, SpriteBatch *spriteBatch);
	~FontRenderer();
	
	void DrawString(const char *text,
					unsigned x,
					unsigned y,
					const Color &color,
					float scale = 0.5f,
					const sm::Matrix& transform = sm::Matrix::Identity);
	
	sm::Point<int> MeasureString(const char *text);
};

