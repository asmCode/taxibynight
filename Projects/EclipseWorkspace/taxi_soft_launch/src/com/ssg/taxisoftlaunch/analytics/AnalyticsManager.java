package com.ssg.taxisoftlaunch.analytics;

import java.util.List;
import java.util.Vector;

import android.content.Context;

public class AnalyticsManager
{
	private static List<IAnalytics> m_analytics = new Vector<IAnalytics>();
	
	public static void Initialize(Context context)
	{
		GameAnalyticsWrapper gameAnalytics = new GameAnalyticsWrapper();
		gameAnalytics.Initialize(context);
		
		m_analytics.add(gameAnalytics);
	}
	
	public static void OnPause()
	{
		for (int i = 0; i < m_analytics.size(); i++)
			m_analytics.get(i).OnPause();
	}
	
	public static void OnResume()
	{
		for (int i = 0; i < m_analytics.size(); i++)
			m_analytics.get(i).OnResume();
	}
	
	public static void LogEvent(String name)
	{
		for (int i = 0; i < m_analytics.size(); i++)
			m_analytics.get(i).LogEvent(name);
	}
	
	public static void LogEvent(String name, String value)
	{
		for (int i = 0; i < m_analytics.size(); i++)
			m_analytics.get(i).LogEvent(name, value);
	}
	
	public static void LogEvent(String name, float value)
	{
		for (int i = 0; i < m_analytics.size(); i++)
			m_analytics.get(i).LogEvent(name, value);
	}
}
