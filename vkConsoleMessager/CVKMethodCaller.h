

#ifndef __C_VK_METHOD_CALLER
#define __C_VK_METHOD_CALLER

#include "CVKAuthorizer.h"
#include "json/json.h"

class CVKMethodCaller
{
protected:
	CVKAuthorizer *auth;
    CLogManager log;

	std::string sendToServer(std::string url, bool useProxy=false) const;
public:
	CVKMethodCaller(CVKAuthorizer *auth);
	~CVKMethodCaller();

	CVKAuthorizer *getAuthorizer() const {return auth;}

	int call(std::string method, Json::Value &responce) const;
};

#endif