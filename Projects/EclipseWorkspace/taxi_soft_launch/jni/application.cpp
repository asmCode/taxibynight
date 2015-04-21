/*
 * Copyright (C) 2009 The Android Open Source Project
 * See accompanying gl_code.cpp for license.
 */

#include "gl_code.h"
#include "StorageHelper.h"
#include "TaxiCode/Bunnies/InfectedBunniesFactory.h"
#include "TaxiCode/Bunnies/Environment.h"
#include "TaxiCode/Bunnies/SystemSpecificData/SystemSpecificData.h"
#include <Graphics/GraphicsEngineFactory.h>

#include <jni.h>
#include <fstream>
#include <vector>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

static const char gVertexShader[] = 
    "attribute vec4 vPosition;\n"
    "void main() {\n"
    "  gl_Position = vPosition;\n"
    "}\n";

static const char gFragmentShader[] = 
    "precision mediump float;\n"
    "void main() {\n"
    "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
    "}\n";
GLuint gProgram;
GLuint gvPositionHandle;

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

	for (uint32_t i = 0; i < assets.size(); i++)
		StorageHelper::UnpackAsset(assetManager, assets[i], dataPath);
}

IGameController* m_game;

bool setupGraphics(AAssetManager* assetManager, const std::string& writablePath, int w, int h)
{
	TaxiGame::Environment::GetInstance()->SetBasePath("./");
	TaxiGame::Environment::GetInstance()->SetWritePath(writablePath);

	TaxiGame::Environment::GetInstance()->SetScreenSize(w, h);

	ProcessAsset(assetManager, writablePath);

	IGraphicsEngine *graphicsEngine = GraphicsEngineFactory::Create();
	m_game = InfectedBunniesFactory::Create(graphicsEngine);
	m_game->Initialize(NULL, NULL);

	/*
	ProcessAsset(assetManager, writablePath);

    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("setupGraphics(%d, %d)", w, h);
    gProgram = createProgram(gVertexShader, gFragmentShader);
    if (!gProgram) {
        LOGE("Could not create program.");
        return false;
    }
    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
            gvPositionHandle);

    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    return true;
    */
}

const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,
        0.5f, -0.5f };

void renderFrame()
{
	/*
    static float grey;
    grey += 0.01f;
    if (grey > 1.0f) {
        grey = 0.0f;
    }
    glClearColor(grey, grey, grey, 1.0f);
    checkGlError("glClearColor");
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");

    glUseProgram(gProgram);
    checkGlError("glUseProgram");

    glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(gvPositionHandle);
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLES, 0, 3);
    checkGlError("glDrawArrays");
    */
}
