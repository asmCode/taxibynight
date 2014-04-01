#include "AnalyticsEvent.h"

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
	m_parameters.push_back(Parameter(paramName, paramValue));
}
