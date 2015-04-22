#include "GameController.h"

#include "IScreen.h"
#include "GameScreen.h"
#include "SplashScreen.h"
#include "MainMenuScreen.h"
#include "SummaryScreen.h"
#include "ComicsScreen.h"
#include "IntroScreen.h"
#include "LeaderboardScreen.h"
#include "SpritesMap.h"
#include "Player.h"
#include "Environment.h"
#include "Control.h"
#include "DrawingRoutines.h"
#include "InterfaceProvider.h"
#include "Leaderboard.h"
#include "AnalyticsProvider.h"
#include "AnalyticsEvents/StartGameEvent.h"
#include "Bonuses/BonusStreetSymbol.h"
#include "Bonuses/BonusBlowEffect.h"
#include <Graphics/IGraphicsEngine.h>
#include <Graphics/Content/Content.h>
#include <Graphics/Model.h>
#include <Graphics/Animation.h>
#include <Graphics/SpriteBatch.h>
#include <Graphics/FontRenderer.h>
#include <Audio/SoundManager.h>
#include "AdsMnager.h"
#include <Utils/Log.h>
#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

GameController::GameController(IGraphicsEngine *graphicsEngine) :
	m_graphicsEngine(graphicsEngine),
	m_splashScreen(NULL),
	m_mainMenuScreen(NULL),
	m_summaryScreen(NULL),
	m_gameScreen(NULL),
	m_comicsScreen(NULL),
	m_activeScreen(NULL)
{
}

GameController::~GameController(void)
{
}

bool GameController::InitializeGraphics(const std::string &basePath)
{
	Log::LogT("Initializing Graphics");

	uint32_t screenWidth = TaxiGame::Environment::GetInstance()->GetScreenWidth();
	uint32_t screenHeight = TaxiGame::Environment::GetInstance()->GetScreenHeight();

	m_content = new Content(m_graphicsEngine);
	InterfaceProvider::m_content = m_content;
	m_content->LoadTextures(basePath + "gui/");
	m_content->LoadTextures(basePath + "textures/");
	m_content->LoadTextures(basePath + "textures/comics/");
	m_content->LoadShaders(basePath + "shaders/");
	m_content->LoadModels(basePath + "models/");
	m_content->LoadAnimations(basePath + "animations/");
	m_content->LoadMaterials(basePath + "materials/");
	m_content->CombineResources();
	
	Texture *gui01 = m_content->Get<Texture>("gui01");
	gui01->BindTexture();
	gui01->SetFilterModel(Texture::Filter_LinearMipmapLinear, Texture::Filter_Linear);
	gui01->GenerateMipmaps();
	
	Texture *gui02 = m_content->Get<Texture>("gui02");
	gui02->BindTexture();
	gui02->SetFilterModel(Texture::Filter_LinearMipmapLinear, Texture::Filter_Linear);
	gui02->GenerateMipmaps();

	Texture *comicsPage = m_content->Get<Texture>("page0");
	comicsPage->BindTexture();
	comicsPage->SetWrappingMode(Texture::Wrap_ClampToEdge);
	comicsPage->SetFilterModel(Texture::Filter_Linear, Texture::Filter_Linear);

	DrawingRoutines::Initialize();
	DrawingRoutines::SetProjectionMatrix(sm::Matrix::PerspectiveMatrix(45.0f, static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 0.1f, 1000.0f));

	Shader *shader = m_content->Get<Shader>("sprite");

	SpriteBatch *spriteBatch = new SpriteBatch(shader, sm::Matrix::Ortho2DMatrix(0, screenWidth, screenHeight, 0));

	SpritesMap *spritesMap = new SpritesMap();
	if (!spritesMap->LoadFromFile(basePath + "gui/SpritesMap.xml", m_content))
		return false;

	InterfaceProvider::m_graphicsEngine = m_graphicsEngine;
	InterfaceProvider::m_spriteBatch = spriteBatch;
	InterfaceProvider::m_spritesMap = spritesMap;
	InterfaceProvider::m_fonts["digital_bold_24"] = FontRenderer::LoadFromFile((basePath + "fonts/digital_bold_24.xml").c_str(), spriteBatch);
	InterfaceProvider::m_fonts["fenix_18"] = FontRenderer::LoadFromFile((basePath + "fonts/fenix_18.xml").c_str(), spriteBatch);
	InterfaceProvider::m_fonts["fenix_26"] = FontRenderer::LoadFromFile((basePath + "fonts/fenix_26.xml").c_str(), spriteBatch);

	Control::SetSpriteBatch(spriteBatch);

	return true;
}

bool GameController::Initialize(ISystemUtils *systemUtils, IServiceProvider* serviceProvider)
{
	Log::StartLog(true);

	m_systemUtils = systemUtils;

	srand(time(NULL));
	
	AdsManager::GetInstance()->Initialize(serviceProvider);

	Player *player = new Player(TaxiGame::Environment::GetInstance()->GetWritePath() + "player.xml");
	player->Load();

	std::string basePath = TaxiGame::Environment::GetInstance()->GetBasePath();

	SoundManager::GetInstance()->Initialize(basePath + "audio/");
	SoundManager::GetInstance()->PlayMusic();

	if (!InitializeGraphics(basePath))
	{
		assert(false);
		return false;
	}

	BonusStreetSymbol::Initialize();
	BonusBlowEffect::Initialize();

	m_gameScreen = new GameScreen(this);
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

	m_comicsScreen = new ComicsScreen(this);
	if (!m_comicsScreen->InitResources())
		return false;

	m_leaderboardScreen = new LeaderboardScreen(this);
	if (!m_leaderboardScreen->InitResources())
		return false;

	m_introScreen = new IntroScreen(this);
	if (!m_introScreen->InitResources())
		return false;
	
	PlayerStats playerStats;

	/*
	Leaderboard::GetInstance()->SendPlayerPoints(
		player->m_id,
		player->m_name,
		player->m_totalMoney,
		player->m_totalCourses);
	 */
	
	Leaderboard::GetInstance()->SendPlayerPoints(playerStats);


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

	SoundManager::GetInstance()->Update();
}

void GameController::HandlePress(int pointId, const sm::Vec2 &point)
{
	assert(m_activeScreen != NULL);

	m_activeScreen->HandlePress(pointId, point);
}

void GameController::HandleRelease(int pointId, const sm::Vec2 &point)
{
	assert(m_activeScreen != NULL);

	m_activeScreen->HandleRelease(pointId, point);
}

void GameController::HandleMove(int pointId, const sm::Vec2 &point)
{
	assert(m_activeScreen != NULL);

	m_activeScreen->HandleMove(pointId, point);
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
	AnalyticsProvider::GetAnalytics()->TrackEvent(StartGameEvent());
	
	IScreen* screen = NULL;

	if (Player::Instance->m_firstRun)
	{
		Player::Instance->m_firstRun = false;
		Player::Instance->Save();

		screen = m_comicsScreen;
	}
	else
	{
		m_gameScreen->Reset();

		screen = m_gameScreen;
	}

	m_activeScreen->Leave();
	m_activeScreen = screen;
	m_activeScreen->Enter();
}

void GameController::ShowMainMenuScreen()
{
	m_mainMenuScreen->UpdateStats();

	m_activeScreen->Leave();
	m_activeScreen = m_mainMenuScreen;
	m_activeScreen->Enter();
}

void GameController::ShowIntroScreen()
{
	m_activeScreen->Leave();
	m_activeScreen = m_introScreen;
	m_activeScreen->Enter();
}

void GameController::ShowLeaderboard()
{
	m_activeScreen->Leave();
	m_activeScreen = m_leaderboardScreen;
	m_activeScreen->Enter();
}

void GameController::ShowSummaryScreen(
	float earn,
	int courses,
	float totalEarn,
	int totalCourses,
	bool record)
{
	m_summaryScreen->SetStatistics(
		earn,
		courses,
		totalEarn,
		totalCourses,
		record);

	m_activeScreen->Leave();
	m_activeScreen = m_summaryScreen;
	m_activeScreen->Enter();
}

bool GameController::proto_IsInGame()
{
	return dynamic_cast<GameScreen*>(m_activeScreen) != NULL;
}

void GameController::HandleEnterForeground()
{
	SoundManager::GetInstance()->PlayMusic();

	if (m_activeScreen == m_gameScreen)
		SoundManager::GetInstance()->StartEngine();
}

void GameController::HandleEnterBackground()
{
	SoundManager::GetInstance()->StopMusic();

	if (m_activeScreen == m_gameScreen)
		SoundManager::GetInstance()->StopEngine();
}

void GameController::HandleBackButton()
{
	if (m_activeScreen == m_mainMenuScreen)
		m_systemUtils->QuitApplication();
	else if (m_activeScreen == m_gameScreen)
		m_gameScreen->ShowPause();
	else if (m_activeScreen == m_leaderboardScreen)
		ShowMainMenuScreen();
}

void GameController::HandleMenukButton()
{

}

