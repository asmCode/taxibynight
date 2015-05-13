package com.semiseriousgames.taxibynight.analytics;

import android.content.Context;

import com.gameanalytics.android.GameAnalytics;
import com.semiseriousgames.taxibynight.GameSettings;

public class GameAnalyticsWrapper implements IAnalytics
{
	private Context m_context;
	
	public void Initialize(Context context)
	{
		m_context = context;
		
		GameAnalytics.initialise(context, GameSettings.GameAnalyticsSecretKey, GameSettings.GameAnalyticsGameKey);
		GameAnalytics.startSession(context);
		GameAnalytics.setDebugLogLevel(GameAnalytics.VERBOSE);
	}
	
	@Override
	public void OnPause()
	{
		GameAnalytics.stopSession();
	}
	
	@Override
	public void OnResume()
	{
		GameAnalytics.startSession(m_context);
	}
	
	@Override
	public void LogEvent(String name)
	{
		GameAnalytics.newDesignEvent(name);
	}

	@Override
	public void LogEvent(String name, String value)
	{
		GameAnalytics.newDesignEvent(name + ":" + value);
	}

	@Override
	public void LogEvent(String name, float value)
	{		
		GameAnalytics.newDesignEvent(name, value);
	}
}