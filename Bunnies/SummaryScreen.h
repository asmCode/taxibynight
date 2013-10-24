#pragma once

#include "IScreen.h"

class SummaryPanel;
class GameController;

class SummaryScreen : public IScreen
{
public:
	SummaryScreen(GameController *gameController);
	~SummaryScreen(void);

	bool InitResources();
	bool ReleaseResources();

	void Draw(float time, float seconds);
	void Update(float time, float seconds);

	void HandleTapGesture(const sm::Vec2 &point);

private:
	GameController *m_gameController;

	SummaryPanel *m_summaryPanel;

	void HandlePress(uint32_t pointIndex, const sm::Vec2 &point);
	void HandleRelease(uint32_t pointIndex, const sm::Vec2 &point);
};

