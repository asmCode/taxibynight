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

package com.semiseriousgames.taxibynight;

import com.semiseriousgames.taxibynight.analytics.AnalyticsManager;

import android.app.Activity;
import android.app.Dialog;
import android.os.Bundle;

public class GL2JNIActivity extends Activity
{
    GL2JNIView mView;
    private Dialog m_splashScreenDialog; 

    @Override protected void onCreate(Bundle icicle)
    {
        super.onCreate(icicle);
               
        AnalyticsManager.Initialize(this);
        
        GL2JNILib.SetMainActivity(this);
        
        mView = new GL2JNIView(getAssets(), this, true, 24, 0);
        mView.setPreserveEGLContextOnPause(true);
        setContentView(mView);
        
        m_splashScreenDialog = new Dialog(this,android.R.style.Theme_Black_NoTitleBar_Fullscreen);
        m_splashScreenDialog.setContentView(R.layout.activity_main);
        m_splashScreenDialog.show();
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
        
        AnalyticsManager.OnPause();
    }

    @Override protected void onResume()
    {
        super.onResume();
        mView.onResume();
        
        AnalyticsManager.OnResume();
    }
    
    @Override public void onBackPressed()
    {	
    	mView.queueEvent(new Runnable()
    	{	
			@Override
			public void run() { mView.HandleBackButton();}
		});
    }
    
    public void DismissSplashScreen()
    {
    	m_splashScreenDialog.dismiss();
    }
}
