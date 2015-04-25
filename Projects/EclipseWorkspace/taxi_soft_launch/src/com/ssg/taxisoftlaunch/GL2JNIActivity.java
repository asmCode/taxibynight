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

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;

import java.io.File;


public class GL2JNIActivity extends Activity {

    GL2JNIView mView;

    @Override protected void onCreate(Bundle icicle)
    {
        super.onCreate(icicle);
        
        Log.d("taxi", "GL2JNIActivity.onCreate");
        
        mView = new GL2JNIView(getAssets(), getApplication(), true, 24, 0);
        mView.setPreserveEGLContextOnPause(true);
        setContentView(mView);
    }
    
    @Override protected void onDestroy()
    {
    	super.onDestroy();
    	mView.onDestroy();
    }

    @Override protected void onPause()
    {
        super.onPause();
        mView.onPause();
    }

    @Override protected void onResume()
    {
        super.onResume();
        mView.onResume();
    }
    
    @Override public void onBackPressed()
    {
    	mView.HandleBackButton();
    }
}
