

#ifndef __C_VK_METHOD_HOLDER
#define __C_VK_METHOD_HOLDER

#include <string>

class CVKMethodHolder
{
protected:
	std::string str;
	bool firstArg;
public:
	CVKMethodHolder(std::string method);
	~CVKMethodHolder();

	CVKMethodHolder &addParameter(std::string name, int val);
	CVKMethodHolder &addParameter(std::string name, std::string val);

	std::string toString() const {return str.size()?str.substr(0, str.size()-1):"";}
};

#endif