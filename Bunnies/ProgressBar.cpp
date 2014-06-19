#include "ProgressBar.h"
#include <assert.h>
#include <Graphics/SpriteBatch.h>
#include <Graphics/TexPart.h>
#include <Graphics/Color.h>
#include <Utils/Log.h>

ProgressBar::ProgressBar(
	const std::string& name,
	const TexPart& bg,
	const TexPart& fg) : Control(name)
{
	SetWidth(bg.ImageRect.Width);
	SetHeight(bg.ImageRect.Height);

	m_bg = bg;
	m_fg = fg;
}

ProgressBar::ProgressBar(
	const std::string& name,
	const TexPart& bg,
	const TexPart& fg,
	int width,
	int height) : Control(name)
{
	SetWidth(width);
	SetHeight(height);

	m_bg = bg;
	m_fg = fg;
}

float ProgressBar::GetValue() const
{
	return m_value;
}

void ProgressBar::SetValue(float value)
{
	m_value = value;
}

void ProgressBar::OnDraw(float time, float ms)
{
	sm::Vec2 globalPos = GetGlobalPos();

	if (m_bg.Tex != NULL)
	{	
		spriteBatch->Draw(m_bg,
			Color(255, 255, 255, (unsigned char)(255.0f * opacity)),
			(int)globalPos.x,
			(int)globalPos.y,
			width,
			height);
	}

	if (m_fg.Tex != NULL)
	{
		TexPart cuttedFg = m_fg;

		cuttedFg.SetImageRect(sm::Rect<int>(
			cuttedFg.ImageRect.X,
			cuttedFg.ImageRect.Y,
			(int)((float)cuttedFg.ImageRect.Width * m_value),
			cuttedFg.ImageRect.Height));

		spriteBatch->Draw(cuttedFg,
			Color(255, 255, 255, (unsigned char)(255.0f * opacity)),
			(int)globalPos.x,
			(int)globalPos.y,
			(int)((float)width * m_value),
			height);
	}
}
