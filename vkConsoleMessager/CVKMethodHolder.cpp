

#include "CVKMethodHolder.h"

#include <stdlib.h>

CVKMethodHolder::CVKMethodHolder(std::string method)
{
    str = method;
    if (str.find("?") == std::string::npos)
        str += "?";
}
CVKMethodHolder::~CVKMethodHolder()
{
}

CVKMethodHolder &CVKMethodHolder::addParameter(std::string name, int val)
{
	str+=name;
	char buf[100];
	sprintf(buf, "%d", val);
	str+='=';
	str+=buf;
	str+='&';
	return *this;
}
CVKMethodHolder &CVKMethodHolder::addParameter(std::string name, std::string val)
{
	str+=name;
	str+='=';
	str+=val;
	str+="&";
	return *this;
}