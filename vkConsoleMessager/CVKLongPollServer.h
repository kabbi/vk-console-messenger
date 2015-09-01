

#ifndef __C_VK_LONG_POLL_SERVER
#define __C_VK_LONG_POLL_SERVER

#include "CVKAuthorizer.h"
#include "json/json.h"

class CVKLongPollServer
{
protected:
    CLogManager log;
    
	std::string sendToServer(std::string url, bool useProxy=false) const;
public:
	CVKLongPollServer();
	~CVKLongPollServer();
    
	int call(Json::Value &params, Json::Value &responce) const;
};

#endif