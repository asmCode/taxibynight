/*
 * Copyright (C) 2007 The Android Open Source Project
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

package com.ssg.taxisoftlaunch;

import android.content.res.AssetManager;

public class GL2JNILib
{
     static
     {
    	 System.loadLibrary("fmod");
         System.loadLibrary("taxisoftlaunch");
     }

     public static native void init(AssetManager javaAssetManager, String writablePath, int width, int height);
     public static native void step();
     public static native void HandlePress(int pointId, float x, float y);
     public static native void HandleRelease(int pointId, float x, float y);
     public static native void HandleMove(int pointId, float x, float y);
     
     public static native void HandleEnterForeground();
     public static native void HandleEnterBackground();
     public static native void HandleBackButton();
     public static native void Destroy();
}
