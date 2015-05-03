package com.semiseriousgames.taxibynight.analytics;

import java.util.HashMap;
import java.util.Map;

import android.content.Context;

import com.flurry.android.FlurryAgent;
import com.semiseriousgames.taxibynight.GameSettings;

public class FlurryAnalyticsWrapper implements IAnalytics
{
	private Context m_context;
	
	public void Initialize(Context context)
	{
		m_context = context;
		
        FlurryAgent.setLogEnabled(true);
        FlurryAgent.init(m_context, GameSettings.FlurryAnalyticsApiKey);
	}
	
	@Override
	public void OnPause()
	{
		// Flurry has automatic session handling since API 14
	}
	
	@Override
	public void OnResume()
	{
		// Flurry has automatic session handling since API 14
	}
	
	@Override
	public void LogEvent(String name)
	{
		FlurryAgent.logEvent(name);
	}

	@Override
	public void LogEvent(String name, String value)
	{
		Map<String, String> params = new HashMap<String, String>();
		params.put(name, value);
		
		FlurryAgent.logEvent(name, params);
	}

	@Override
	public void LogEvent(String name, float value)
	{		
		Map<String, String> params = new HashMap<String, String>();
		params.put(name, Float.toString(value));
		
		FlurryAgent.logEvent(name, params);
	}
}
