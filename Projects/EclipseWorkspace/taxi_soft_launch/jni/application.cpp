/*
 * Copyright (C) 2009 The Android Open Source Project
 * See accompanying gl_code.cpp for license.
 */

#include "gl_code.h"
#include "StorageHelper.h"

#include <jni.h>
#include <fstream>

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
	std::string unpackedAssetPath = StorageHelper::UnpackAsset(assetManager, "01.bmp", writablePath);

	std::ifstream file(unpackedAssetPath.c_str(), std::ios::binary);

	char data;
	file.read(&data, 1);
	LOGI("byte 1: %c", data);
	file.read(&data, 1);
	LOGI("byte 2: %c", data);
	file.read(&data, 1);
	LOGI("byte 3: %c", data);

	file.close();

}

bool setupGraphics(AAssetManager* assetManager, const std::string& writablePath, int w, int h)
{
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
}

const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,
        0.5f, -0.5f };

void renderFrame() {
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
}
