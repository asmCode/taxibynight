#pragma once

#include "IScreen.h"
#include "Ticker.h"
#include <Graphics/Texture.h>
#include <string>

class GameController;

class ComicsScreen : public IScreen
{
public:
	ComicsScreen(GameController *gameController);
	~ComicsScreen(void);

	bool InitResources();
	bool ReleaseResources();

	void Draw(float time, float seconds);
	void Update(float time, float seconds);

private:
	static const int PagesCount = 3;
	static const int PageTimeout = 4;
	static const std::string PageFileNameTemplate;

	int m_pageIndex;

	GameController *m_gameController;

	Texture* m_pages[PagesCount];

	Ticker m_timeout;

	void NextPage();

	void Leave();

	void HandlePress(int pointId, const sm::Vec2 &point);
};

