#pragma once

#include "Control.h"

class ProgressBar : public Control
{
public:
	ProgressBar(const std::string& name,
				const TexPart& bg,
				const TexPart& fg);

	ProgressBar(const std::string& name,
				const TexPart& bg,
				const TexPart& fg,
				int width,
				int height);

	float GetValue() const;
	void SetValue(float value);

private:
	float m_value;

	TexPart m_bg;
	TexPart m_fg;

	virtual void OnDraw(float time, float ms);
};
