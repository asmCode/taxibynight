#include "GameController.h"

#include "IScreen.h"
#include "GameScreen.h"
#include "SplashScreen.h"
#include "MainMenuScreen.h"
#include "SummaryScreen.h"
#include "SpritesMap.h"
#include "Environment.h"
#include "Control.h"
#include "DrawingRoutines.h"
#include "InterfaceProvider.h"
#include <Graphics/IGraphicsEngine.h>
#include <Graphics/Content/Content.h>
#include <Graphics/Model.h>
#include <Graphics/Animation.h>
#include <Graphics/SpriteBatch.h>
#include <Graphics/FontRenderer.h>
#include <Utils/Log.h>
#include <stddef.h>
#include <assert.h>

GameController::GameController(IGraphicsEngine *graphicsEngine) :
	m_graphicsEngine(graphicsEngine),
	m_splashScreen(NULL),
	m_mainMenuScreen(NULL),
	m_summaryScreen(NULL),
	m_gameScreen(NULL),
	m_activeScreen(NULL)
{
}

GameController::~GameController(void)
{
}

bool GameController::InitializeGraphics(const std::string &basePath)
{
	Log::StartLog(true, false, false);
	Log::LogT("Initializing Graphics");

	uint32_t screenWidth = TaxiGame::Environment::GetInstance()->GetScreenWidth();
	uint32_t screenHeight = TaxiGame::Environment::GetInstance()->GetScreenHeight();

	m_content = new Content(m_graphicsEngine);
	InterfaceProvider::m_content = m_content;
	m_content->LoadTextures(basePath + "data/gui/");
	m_content->LoadTextures(basePath + "data/textures/");
	m_content->LoadShaders(basePath + "data/shaders/");
	m_content->LoadModels(basePath + "data/models/");
	m_content->LoadAnimations(basePath + "data/animations/");
	m_content->LoadMaterials(basePath + "data/materials/");
	m_content->CombineResources();

	DrawingRoutines::Initialize();
	DrawingRoutines::SetProjectionMatrix(sm::Matrix::PerspectiveMatrix(45.0f, static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.1f, 1000.0f));

	Shader *shader = m_content->Get<Shader>("sprite");

	SpriteBatch *spriteBatch = new SpriteBatch(shader, sm::Matrix::Ortho2DMatrix(0, screenWidth, screenHeight, 0));

	SpritesMap *spritesMap = new SpritesMap();
	if (!spritesMap->LoadFromFile(basePath + "data/gui/SpritesMap.xml", m_content))
		return false;

	InterfaceProvider::m_graphicsEngine = m_graphicsEngine;
	InterfaceProvider::m_spriteBatch = spriteBatch;
	InterfaceProvider::m_spritesMap = spritesMap;
	InterfaceProvider::m_fontRenderer = FontRenderer::LoadFromFile((basePath + "data/fonts/komika_title_32.xml").c_str(), spriteBatch);

	Control::SetSpriteBatch(spriteBatch);
	
	return true;
}

bool GameController::Initialize()
{
	std::string basePath = TaxiGame::Environment::GetInstance()->GetBasePath();

	if (!InitializeGraphics(basePath))
	{
		assert(false);
		return false;
	}

	m_gameScreen = new GameScreen();
	if (!m_gameScreen->Initialize())
		return false;

	m_splashScreen = new SplashScreen(this);
	if (!m_splashScreen->InitResources())
		return false;

	m_mainMenuScreen = new MainMenuScreen(this);
	if (!m_mainMenuScreen->InitResources())
		return false;

	m_summaryScreen = new SummaryScreen(this);
	if (!m_summaryScreen->InitResources())
		return false;

	m_activeScreen = m_splashScreen;

	return true;
}

void GameController::Draw(float time, float seconds)
{
	assert(m_activeScreen != NULL);

	m_activeScreen->Draw(time, seconds);
}

void GameController::Update(float time, float seconds)
{
	assert(m_activeScreen != NULL);

	m_activeScreen->Update(time, seconds);
}

void GameController::HandleTapGesture(const sm::Vec2 &point)
{
	assert(m_activeScreen != NULL);

	m_activeScreen->HandleTapGesture(point);
}

void GameController::HandlePress(uint32_t pointIndex, const sm::Vec2 &point)
{
	assert(m_activeScreen != NULL);

	m_activeScreen->HandlePress(pointIndex, point);
}

void GameController::HandleRelease(uint32_t pointIndex, const sm::Vec2 &point)
{
	assert(m_activeScreen != NULL);

	m_activeScreen->HandleRelease(pointIndex, point);
}

void GameController::HandleMove(uint32_t pointIndex, const sm::Vec2 &point)
{
	assert(m_activeScreen != NULL);

	m_activeScreen->HandleMove(pointIndex, point);
}

void GameController::proto_SetStrafeMove(float value)
{
}

void GameController::proto_SetForwardMove(float value)
{
}

void GameController::proto_SetLookTarget(const sm::Vec3 &lookTarget)
{
}

void GameController::ShowGameScreen()
{
	m_activeScreen = m_gameScreen;
}

void GameController::ShowMainMenuScreen()
{
	//m_activeScreen = m_mainMenuScreen;
	m_activeScreen = m_summaryScreen;
}

bool GameController::proto_IsInGame()
{
	return dynamic_cast<GameScreen*>(m_activeScreen) != NULL;
}

