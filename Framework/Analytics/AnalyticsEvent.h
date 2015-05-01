#ifndef ANALYTICS_EVENT
#define ANALYTICS_EVENT

#include <string>
#include <vector>

class AnalyticsEvent
{
public:
	enum ParamType
	{
		ParamType_None,
		ParamType_String,
		ParamType_Float,
		ParamType_Custom
	};

	AnalyticsEvent(const std::string& eventName);
	AnalyticsEvent(const std::string& eventName, const std::string& param);
	AnalyticsEvent(const std::string& eventName, float param);

	ParamType GetParamType() const;
	const std::string& GetEventName() const;
	const std::string& GetParamString() const;
	float GetParamFloat() const;

	int GetParametersCount() const;
	std::string GetParameterName(int index) const;
	std::string GetParameterValue(int index) const;
	
protected:
	void AddEventParameter(const std::string& paramName, const std::string& paramValue);
	
private:
	typedef std::pair<std::string, std::string> Parameter;
	typedef std::vector<Parameter> ParametersVector;
	
	ParametersVector m_parameters;

	ParamType m_paramType;
	std::string m_eventName;
	std::string m_eventParamS;
	float m_eventParamF;
};

#endif // ANALYTICS_EVENT

