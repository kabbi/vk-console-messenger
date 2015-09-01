

#include "CVKAuthorizer.h"
#include <sstream>

const char *privNames[]={
	"notify", "friends", "photos", "audio", "video", "docs", "notes", "pages",
	"offers", "questions", "wall", "groups", "messages", "notifications", "ads", "offline", "nohttps"
};

CVKAuthorizer::CVKAuthorizer(int appId)
	: appId(appId), privs(0), expire(0), userId(0)
{
}
CVKAuthorizer::~CVKAuthorizer()
{
}

int CVKAuthorizer::getAppId() const
{
	return appId;
}

void CVKAuthorizer::setPriviledges(int priv)
{
	privs=priv;
}
int CVKAuthorizer::getPriviledges() const
{
	return privs;
}

bool CVKAuthorizer::isPriviledgeSet(E_VK_PRIVILEDGES priv) const
{
	return privs&priv;
}
void CVKAuthorizer::setPriviledge(E_VK_PRIVILEDGES priv, bool flag)
{
	privs&=~priv;
	if (flag)
		privs|=priv;
}

void CVKAuthorizer::setUserId(int id)
{
	userId=id;
}
int CVKAuthorizer::getUserId() const
{
	return userId;
}

int CVKAuthorizer::getExpireTime() const
{
	return expire;
}

void CVKAuthorizer::setAccessToken(std::string str)
{
	accessToken=str;
}
std::string CVKAuthorizer::getAccessToken() const
{
	return accessToken;
}

std::string CVKAuthorizer::getAuthString() const
{
	// string format example:
	// httpx://oauth.vkontakte.ru/authorize?client_id=1936127&scope=notify&redirect_uri=httpx://oauth.vkontakte.ru/blank.html&display=page&response_type=token

	std::stringstream str;
	str<<"http://oauth.vk.com/authorize?client_id=";
	str<<appId<<"&scope=";
	for (int i=0; i<VK_PRIV_COUNT; i++)
		if (privs & (1<<i))
			str<<privNames[i]<<',';
	str<<"&redirect_uri=http://api.vk.com/blank.html&display=page&response_type=token";
	return str.str();
}

void CVKAuthorizer::parseResponce(std::string str)
{
	// format example: access_token=7d8c29ee33a528687c38cb35887c97390177c8a7c8aa3fedd822c834bef1956&expires_in=86400&user_id=17209872
	size_t firstEqual=str.find_first_of('=');
    if (firstEqual == std::string::npos)
        return;
    firstEqual++;
	size_t firstAnd=str.find_first_of('&');
    if (firstAnd == std::string::npos || firstAnd <= firstEqual)
        return;
	size_t tokenSize=firstAnd-firstEqual;
	accessToken=str.substr(firstEqual, tokenSize);
	sscanf(str.substr(firstAnd+1).c_str(), "expires_in=%u&user_id=%u", &expire, &userId);
}