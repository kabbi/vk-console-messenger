

#include "CVKUser.h"

#include "CVKMethodHolder.h"
#include <fstream>
using namespace std;

CVKUser::CVKUser(Json::Value &user)
	: user(user), uid(user.get("uid", Json::Value(-1)).asInt())
{
}
CVKUser::CVKUser(CVKMethodCaller *caller, int uid)
	: uid(uid)
{
	if (isInCache(uid))
		loadFromCache();
	else
		fetchData(caller);
}
CVKUser::~CVKUser()
{
}

void CVKUser::loadFromCache()
{
	user=cache[uid];
}
void CVKUser::saveToCache()
{
	cache[uid]=user;
}

bool CVKUser::isInCache(int uid)
{
	return cache.find(uid)!=cache.end();
}


void CVKUser::fetchData(CVKMethodCaller *caller)
{
	caller->call(CVKMethodHolder("getProfiles")
		.addParameter("uids", uid)
		.addParameter("fields", "uid,first_name,last_name,nickname,screen_name,sex,bdate,city,country,timezone,photo,photo_medium,photo_big,has_mobile,rate,contacts,education,online,counters")
		.toString(), user);
	user=user["response"][0];
	saveToCache();
}

std::string CVKUser::getFullName() const
{
	if (!user["first_name"].isString() || !user["last_name"].isString())
		return "";
	return user["first_name"].asString()+" "+user["last_name"].asString();
}

std::map<int, Json::Value> CVKUser::cache;