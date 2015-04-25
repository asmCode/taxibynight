/*
 * Copyright (C) 2009 The Android Open Source Project
 * See accompanying gl_code.cpp for license.
 */

#include "gl_code.h"
#include "StorageHelper.h"
#include "AndroidSystemUtils.h"
#include "TaxiCode/Bunnies/InfectedBunniesFactory.h"
#include "TaxiCode/Bunnies/Environment.h"
#include "TaxiCode/Bunnies/SystemSpecificData/SystemSpecificData.h"
#include <Graphics/GraphicsEngineFactory.h>
#include <IO/Path.h>

#include <jni.h>
#include <fstream>
#include <vector>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

void ProcessAsset(AAssetManager* assetManager, const std::string& writablePath)
{
	std::vector<std::string> assets;
	assets.push_back("data/textures/antimagnet.png");
	assets.push_back("data/textures/blade.png");
	assets.push_back("data/textures/bonus.png");
	assets.push_back("data/textures/bonus_blow.png");
	assets.push_back("data/textures/cabby_carma_diff.png");
	assets.push_back("data/textures/cabby_diff.png");
	assets.push_back("data/textures/circle.png");
	assets.push_back("data/textures/flat_1_diffuse.png");
	assets.push_back("data/textures/flat_2_diffuse.png");
	assets.push_back("data/textures/flat_3_diffuse.png");
	assets.push_back("data/textures/guy.png");
	assets.push_back("data/textures/lights.png");
	assets.push_back("data/textures/misc_diffuse.png");
	assets.push_back("data/textures/shadow_tex.png");
	assets.push_back("data/textures/street_1_cross.png");
	assets.push_back("data/textures/street_1_straight.png");
	assets.push_back("data/textures/street_1_t.png");
	assets.push_back("data/textures/street_1_turn.png");
	assets.push_back("data/textures/street_map.png");
	assets.push_back("data/textures/street_pavement.png");
	assets.push_back("data/textures/comics/page0.png");
	assets.push_back("data/textures/comics/page1.png");
	assets.push_back("data/textures/comics/page2.png");

	assets.push_back("data/shaders/Diff.fpr");
	assets.push_back("data/shaders/Diff.vpr");
	assets.push_back("data/shaders/DiffLight.fpr");
	assets.push_back("data/shaders/DiffLight.vpr");
	assets.push_back("data/shaders/DiffTex.fpr");
	assets.push_back("data/shaders/DiffTex.vpr");
	assets.push_back("data/shaders/Ped.fpr");
	assets.push_back("data/shaders/Ped.vpr");
	assets.push_back("data/shaders/sprite.fpr");
	assets.push_back("data/shaders/sprite.vpr");
	assets.push_back("data/shaders/Sprite2.fpr");
	assets.push_back("data/shaders/Sprite2.vpr");
	assets.push_back("data/shaders/Unlit.fpr");
	assets.push_back("data/shaders/Unlit.vpr");

	assets.push_back("data/models/antimagnet.geo");
	assets.push_back("data/models/arrow.geo");
	assets.push_back("data/models/blade.geo");
	assets.push_back("data/models/bonus.geo");
	assets.push_back("data/models/lights.geo");
	assets.push_back("data/models/passenger.geo");
	assets.push_back("data/models/ped_shadow.geo");
	assets.push_back("data/models/skycrapper01.geo");
	assets.push_back("data/models/skycrapper02.geo");
	assets.push_back("data/models/skycrapper03.geo");
	assets.push_back("data/models/street.geo");
	assets.push_back("data/models/taxi.geo");
	assets.push_back("data/models/taxi_shadow.geo");

	assets.push_back("data/materials/arrow.mat");
	assets.push_back("data/materials/blade.mat");
	assets.push_back("data/materials/bonus.mat");
	assets.push_back("data/materials/flat_1.mat");
	assets.push_back("data/materials/flat_2.mat");
	assets.push_back("data/materials/flat_3.mat");
	assets.push_back("data/materials/lights.mat");
	assets.push_back("data/materials/Material #1.mat");
	assets.push_back("data/materials/passenger.mat");
	assets.push_back("data/materials/ped.mat");
	assets.push_back("data/materials/ped_shadow.mat");
	assets.push_back("data/materials/street.mat");
	assets.push_back("data/materials/taxi.mat");
	assets.push_back("data/materials/taxi_shadow.mat");

	assets.push_back("data/gui/BonusControl.xml");
	assets.push_back("data/gui/gui01.png");
	assets.push_back("data/gui/gui02.png");
	assets.push_back("data/gui/HUD.xml");
	assets.push_back("data/gui/IntroPanel.xml");
	assets.push_back("data/gui/LeaderboardPanel.xml");
	assets.push_back("data/gui/MainMenuPanel.xml");
	assets.push_back("data/gui/PausePanel.xml");
	assets.push_back("data/gui/SplashScreen.png");
	assets.push_back("data/gui/SpritesMap.xml");
	assets.push_back("data/gui/SummaryPanel.xml");

	assets.push_back("data/fonts/digital_bold_24.png");
	assets.push_back("data/fonts/digital_bold_24.xml");
	assets.push_back("data/fonts/fenix_18.png");
	assets.push_back("data/fonts/fenix_18.xml");
	assets.push_back("data/fonts/fenix_26.png");
	assets.push_back("data/fonts/fenix_26.xml");

	assets.push_back("data/audio/bonus.mp3");
	assets.push_back("data/audio/button.mp3");
	assets.push_back("data/audio/city_ambient.mp3");
	assets.push_back("data/audio/collision01.mp3");
	assets.push_back("data/audio/collision02.mp3");
	assets.push_back("data/audio/collision03.mp3");
	assets.push_back("data/audio/die.mp3");
	assets.push_back("data/audio/doors.mp3");
	assets.push_back("data/audio/engine.mp3");
	assets.push_back("data/audio/money.mp3");
	assets.push_back("data/audio/summary.mp3");

	std::string dataPath = writablePath + "/taxi_data/";
	DIR* dataDir = opendir(dataPath.c_str());

	if (dataDir != NULL)
		return;

	mkdir(dataPath.c_str(), S_IRWXU |S_IRWXG| S_IRWXO);
	mkdir((dataPath + "/audio").c_str(), S_IRWXU |S_IRWXG| S_IRWXO);
	mkdir((dataPath + "/fonts").c_str(), S_IRWXU |S_IRWXG| S_IRWXO);
	mkdir((dataPath + "/gui").c_str(), S_IRWXU |S_IRWXG| S_IRWXO);
	mkdir((dataPath + "/materials").c_str(), S_IRWXU |S_IRWXG| S_IRWXO);
	mkdir((dataPath + "/models").c_str(), S_IRWXU |S_IRWXG| S_IRWXO);
	mkdir((dataPath + "/shaders").c_str(), S_IRWXU |S_IRWXG| S_IRWXO);
	mkdir((dataPath + "/textures").c_str(), S_IRWXU |S_IRWXG| S_IRWXO);
	mkdir((dataPath + "/textures/comics").c_str(), S_IRWXU |S_IRWXG| S_IRWXO);

	for (uint32_t i = 0; i < assets.size(); i++)
		StorageHelper::UnpackAsset(assetManager, assets[i], dataPath);
}

IGameController* m_game = NULL;
float gameTime = 0.0f;
uint64_t lastTime;

uint64_t GetTimestamp()
{
	static struct timespec _time;

	clock_gettime(CLOCK_MONOTONIC, &_time);
	return (uint64_t)_time.tv_sec * 1000000000LL + _time.tv_nsec;
}

bool setupGraphics(AAssetManager* assetManager, const std::string& writablePath, int w, int h)
{
	LOGI("setupGraphics()");

	if (m_game != NULL)
		Destroy();

	TaxiGame::Environment::GetInstance()->SetBasePath(writablePath + "/taxi_data/");
	TaxiGame::Environment::GetInstance()->SetWritePath(writablePath);
	TaxiGame::Environment::GetInstance()->SetScreenSize(w, h);

	ProcessAsset(assetManager, writablePath);

	IGraphicsEngine *graphicsEngine = GraphicsEngineFactory::Create();
	m_game = InfectedBunniesFactory::Create(graphicsEngine);

	AndroidSystemUtils* systemUtils = new AndroidSystemUtils();
	m_game->Initialize(systemUtils, NULL);

	lastTime = GetTimestamp();

	return true;
}

void Destroy()
{
	LOGI("Destroy(), m_game = %x", m_game);

	if (m_game != NULL)
	{
		delete m_game;
		m_game = NULL;
	}
}

void renderFrame()
{
	if (m_game == NULL)
		return;

	uint64_t timeNow = GetTimestamp();
	float deltaTime = (float)(timeNow - lastTime) / 1000000000.0f;
	lastTime = timeNow;
	gameTime += deltaTime;

	m_game->Update(gameTime, deltaTime);
	m_game->Draw(gameTime, deltaTime);
}

void HandlePress(int pointId, float x, float y)
{
	if (m_game != NULL)
		m_game->HandlePress(pointId, sm::Vec2(x, y));
}

void HandleRelease(int pointId, float x, float y)
{
	if (m_game != NULL)
		m_game->HandleRelease(pointId, sm::Vec2(x, y));
}

void HandleMove(int pointId, float x, float y)
{
	if (m_game != NULL)
		m_game->HandleMove(pointId, sm::Vec2(x, y));
}

void HandleEnterForeground()
{
	if (m_game != NULL)
		m_game->HandleEnterForeground();
}

void HandleEnterBackground()
{
	if (m_game != NULL)
		m_game->HandleEnterBackground();
}

void HandleBackButton()
{
	if (m_game != NULL)
		m_game->HandleBackButton();
}

