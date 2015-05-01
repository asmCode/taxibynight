#include "AnalyticsEvent.h"

AnalyticsEvent::AnalyticsEvent(const std::string& eventName) :
	m_paramType(ParamType_None),
	m_eventName(eventName)
{
}

AnalyticsEvent::AnalyticsEvent(const std::string& eventName, const std::string& param) :
	m_paramType(ParamType_String),
	m_eventName(eventName),
	m_eventParamS(param)
{
}

AnalyticsEvent::AnalyticsEvent(const std::string& eventName, float param) :
	m_paramType(ParamType_Float),
	m_eventName(eventName),
	m_eventParamF(param)
{
}

AnalyticsEvent::ParamType AnalyticsEvent::GetParamType() const
{
	return m_paramType;
}

const std::string& AnalyticsEvent::GetEventName() const
{
	return m_eventName;
}

const std::string& AnalyticsEvent::GetParamString() const
{
	return m_eventParamS;
}

float AnalyticsEvent::GetParamFloat() const
{
	return m_eventParamF;
}

int AnalyticsEvent::GetParametersCount() const
{
	return m_parameters.size();
}

std::string AnalyticsEvent::GetParameterName(int index) const
{
	return m_parameters[index].first;
}

std::string AnalyticsEvent::GetParameterValue(int index) const
{
	return m_parameters[index].second;
}

void AnalyticsEvent::AddEventParameter(const std::string& paramName, const std::string& paramValue)
{
	m_paramType = ParamType_Custom;

	m_parameters.push_back(Parameter(paramName, paramValue));
}
