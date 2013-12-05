#include "ComicsScreen.h"
#include "InterfaceProvider.h"
#include "GameProps.h"
#include "GameController.h"
#include "Environment.h"
#include "Audio/SoundManager.h"
#include <Graphics/Content/Content.h>
#include <Graphics/SpriteBatch.h>
#include <stdio.h>

const std::string ComicsScreen::PageFileNameTemplate = "page%d";

ComicsScreen::ComicsScreen(GameController *gameController) :
	m_pageIndex(0),
	m_gameController(gameController),
	m_timeout(PageTimeout)
{
}

ComicsScreen::~ComicsScreen(void)
{
}

bool ComicsScreen::InitResources()
{
	for (unsigned int i = 0; i < PagesCount; i++)
	{
		char pageName[128];
		sprintf(pageName, PageFileNameTemplate.c_str(), i);
		m_pages[i] = InterfaceProvider::GetContent()->Get<Texture>(pageName);
		assert(m_pages[i] != NULL);
	}

	return true;
}

bool ComicsScreen::ReleaseResources()
{
	return true;
}

void ComicsScreen::Draw(float time, float seconds)
{
	InterfaceProvider::GetSpriteBatch()->Begin();
	InterfaceProvider::GetSpriteBatch()->Draw(m_pages[m_pageIndex], 0, 0,
		TaxiGame::Environment::GetInstance()->GetScreenWidth(),
		TaxiGame::Environment::GetInstance()->GetScreenHeight());
	InterfaceProvider::GetSpriteBatch()->End();
}

void ComicsScreen::Update(float time, float seconds)
{
	m_timeout.Progress(seconds);
	if (m_timeout.IsTimeout())
		NextPage();
}

void ComicsScreen::NextPage()
{
	m_timeout.Reset();
	m_pageIndex++;

	if (m_pageIndex == PagesCount)
		m_gameController->ShowGameScreen();
}

void ComicsScreen::Leave()
{
	for (unsigned int i = 0; i < PagesCount; i++)
		delete m_pages[i];
}

void ComicsScreen::HandlePress(int pointId, const sm::Vec2 &point)
{
	SoundManager::GetInstance()->PlaySound(SoundManager::Sound_Button);
	NextPage();
}
