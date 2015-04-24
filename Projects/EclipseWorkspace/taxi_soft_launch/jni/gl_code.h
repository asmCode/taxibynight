/*
 * Copyright (C) 2009 The Android Open Source Project
 * See accompanying gl_code.cpp for license.
 */

#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <string>

#define  LOG_TAG    "taxi"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

class AAssetManager;

extern bool setupGraphics(AAssetManager* assetManager, const std::string& writablePath, int w, int h);
extern void renderFrame();
extern void printGLString(const char *name, GLenum s);
extern void checkGlError(const char* op);
