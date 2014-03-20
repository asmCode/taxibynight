#include "HttpCommunication.h"
#include <Utils/Log.h>
#include <Utils/StringUtils.h>

HttpCommunication::HttpCommunication(const std::string& hostAddress)
{
}

HttpCommunication::~HttpCommunication()
{
}

void HttpCommunication::AddObserver(IHttpCommunicationObserver* observer)
{
	m_observer = observer;
}

void HttpCommunication::SendRequest(const std::string& address)
{
}

bool HttpCommunication::IsBusy() const
{
	return false;
}
