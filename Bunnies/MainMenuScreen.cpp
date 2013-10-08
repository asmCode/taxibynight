#include "MainMenuScreen.h"
#include "InterfaceProvider.h"
#include "GameProps.h"
#include "GameController.h"
#include "MainMenuPanel.h"
#include <Graphics/Content/Content.h>
#include <Graphics/SpriteBatch.h>

MainMenuScreen::MainMenuScreen(GameController *gameController) :
	m_gameController(gameController),
	m_mainMenuPanel(NULL)
{
}


MainMenuScreen::~MainMenuScreen(void)
{
}

bool MainMenuScreen::InitResources()
{
	m_mainMenuPanel = MainMenuPanel::Create(m_gameController);

	return true;
}

bool MainMenuScreen::ReleaseResources()
{
	return true;
}

void MainMenuScreen::Draw(float time, float seconds)
{
	InterfaceProvider::GetSpriteBatch()->Begin();
	m_mainMenuPanel->Draw(time, seconds);
	InterfaceProvider::GetSpriteBatch()->End();
}

void MainMenuScreen::Update(float time, float seconds)
{
}

void MainMenuScreen::HandleRelease(uint32_t pointIndex, const sm::Vec2 &point)
{
	m_mainMenuPanel->HandleRelease(pointIndex, point);
}

void MainMenuScreen::HandleTapGesture(const sm::Vec2 &point)
{
	m_mainMenuPanel->HandleTapGesture(point);
}

