

#ifndef __C_VK_AUTHORIZER
#define __C_VK_AUTHORIZER

#include <string>
#include "CLogManager.h"

enum E_VK_PRIVILEDGES
{
	VK_PRIV_NOTIFY			=1,
	VK_PRIV_FRIENDS			=2,
	VK_PRIV_PHOTOS			=4,
	VK_PRIV_AUDIO			=8,
	VK_PRIV_VIDEO			=16,
	VK_PRIV_DOCS			=32,
	VK_PRIV_NOTES			=64,
	VK_PRIV_PAGES			=128,
	VK_PRIV_OFFERS			=256,
	VK_PRIV_QUESTIONS		=512,
	VK_PRIV_WALL			=1024,
	VK_PRIV_GROUPS			=2048,
	VK_PRIV_MESSAGES		=4096,
	VK_PRIV_NOTIFICATIONS	=8192,
	VK_PRIV_ADS				=16384,
	VK_PRIV_OFFLINE			=32768,
	VK_PRIV_NOHTTPS			=65536,
	VK_PRIV_COUNT			=17
};

class CVKAuthorizer
{
protected:
	int privs;
	const int appId;
	std::string accessToken;
	int expire;
	int userId;
    
    CLogManager log;
public:
	CVKAuthorizer(int appId);
	~CVKAuthorizer();

	int getAppId() const;

	void setPriviledges(int priv);
	int getPriviledges() const;

	bool isPriviledgeSet(E_VK_PRIVILEDGES priv) const;
	void setPriviledge(E_VK_PRIVILEDGES priv, bool flag);

	void setUserId(int id);
	int getUserId() const;

	int getExpireTime() const;

	void setAccessToken(std::string str);
	std::string getAccessToken() const;

	std::string getAuthString() const;
	void parseResponce(std::string str);
};

#endif