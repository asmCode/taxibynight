#ifndef HTTPCOMMUNICATION_H_
#define HTTPCOMMUNICATION_H_

#include "IHttpCommunicationObserver.h"
#include <string>

class HttpCommunication
{
public:
	HttpCommunication(const std::string& hostAddress);
	virtual ~HttpCommunication();

	void AddObserver(IHttpCommunicationObserver* observer);
	void SendRequest(const std::string& address);

	bool IsBusy() const;

private:
	IHttpCommunicationObserver* m_observer;

	bool m_isBusy;
};

#endif /* HTTPCOMMUNICATION_H_ */
