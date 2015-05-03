package com.semiseriousgames.taxibynight.analytics;

public interface IAnalytics
{
	public void LogEvent(String name);
	public void LogEvent(String name, String value);
	public void LogEvent(String name, float value);
	
	public void OnPause();
	public void OnResume();
}
