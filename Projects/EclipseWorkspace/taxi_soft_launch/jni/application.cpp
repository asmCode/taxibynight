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
