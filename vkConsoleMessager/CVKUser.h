

#ifndef __C_VK_USER
#define __C_VK_USER

#include "CVKMethodCaller.h"

class CVKUser
{
protected:
	int uid;

	Json::Value user;
	static std::map<int, Json::Value> cache;

	void loadFromCache();
	void saveToCache();
	void fetchData(CVKMethodCaller *auth);
public:
	CVKUser(Json::Value &user);
	CVKUser(CVKMethodCaller *caller, int uid=1);
	~CVKUser();

	Json::Value getJson() {return user;}
	std::string getFullName() const;

	bool isInCache(int uid);
};

#endif