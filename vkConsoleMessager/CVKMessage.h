

#ifndef __C_VK_MESSAGE
#define __C_VK_MESSAGE

#include "json/json.h"

enum MessageFlag
{
    VK_MF_UNREAD    = (1<<0),
    VK_MF_OUTBOX    = (1<<1),
    VK_MF_REPLIED   = (1<<2),
    VK_MF_IMPORTANT = (1<<3),
    VK_MF_CHAT      = (1<<4),
    VK_MF_FRIENDS   = (1<<5),
    VK_MF_SPAM      = (1<<6),
    VK_MF_DELETED   = (1<<7),
    VK_MF_FIXED     = (1<<8),
    VK_MF_MEDIA     = (1<<9)
};

class CVKMessage
{
protected:
	Json::Value msg;
public:
	CVKMessage(Json::Value &msg);
	~CVKMessage();

	Json::Value &getJson() {return msg;}
};

#endif