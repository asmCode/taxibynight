/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// OpenGL ES 2.0 code

#include <jni.h>
#include <android/asset_manager_jni.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string>

#include "gl_code.h"


void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

extern "C" {
    JNIEXPORT void JNICALL Java_com_ssg_taxisoftlaunch_GL2JNILib_init(
    		JNIEnv * env,
			jobject obj,
			jobject javaAssetManager,
			jstring javaWritablePath,
			jint width,
			jint height);

    JNIEXPORT void JNICALL Java_com_ssg_taxisoftlaunch_GL2JNILib_step(JNIEnv * env, jobject obj);
};

JNIEXPORT void JNICALL Java_com_ssg_taxisoftlaunch_GL2JNILib_init(
		JNIEnv * env,
		jobject obj,
		jobject javaAssetManager,
		jstring javaWritablePath,
		jint width,
		jint height)
{


	sleep(0);

	AAssetManager* assetManager = AAssetManager_fromJava(env, javaAssetManager);

	const jsize len = env->GetStringUTFLength(javaWritablePath);
	const char* writablePath = env->GetStringUTFChars(javaWritablePath, (jboolean*)0);

    setupGraphics(assetManager, std::string(writablePath, len), width, height);
}

JNIEXPORT void JNICALL Java_com_ssg_taxisoftlaunch_GL2JNILib_step(JNIEnv * env, jobject obj)
{
    renderFrame();
}
