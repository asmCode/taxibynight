#ifndef ANALYTICS_EVENT
#define ANALYTICS_EVENT

#include <string>
#include <vector>

class AnalyticsEvent
{
public:
	int GetParametersCount() const;
	std::string GetParameterName(int index) const;
	std::string GetParameterValue(int index) const;
	
	virtual std::string GetEventName() const = 0;
	
protected:
	void AddEventParameter(const std::string& paramName, const std::string& paramValue);
	
private:
	typedef std::pair<std::string, std::string> Parameter;
	typedef std::vector<Parameter> ParametersVector;
	
	ParametersVector m_parameters;
};

#endif // ANALYTICS_EVENT

