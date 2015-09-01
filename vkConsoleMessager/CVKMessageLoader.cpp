

#include "CVKMessageLoader.h"

#include "CVKMethodHolder.h"
using namespace std;

CVKMessageLoader::CVKMessageLoader(CVKMethodCaller *caller)
	: caller(caller)
{
}
CVKMessageLoader::~CVKMessageLoader()
{
}

void CVKMessageLoader::loadHive(CVKChat &chat, int id, bool dialog)
{
	int msgCount=0;
	int totalRead=0;
	while (true)
	{
		Json::Value history;
		caller->call(CVKMethodHolder("messages.getHistory")
			.addParameter(dialog?"chat_id":"uid", id)
			.addParameter("offset", totalRead)
			.addParameter("count", 100)
			.toString(), history);

		msgCount=history["response"][0].asInt();

		for (int i=1; i<history["response"].size(); i++)
			chat.addMessage(new CVKMessage(history["response"][i]));

		totalRead+=history["response"].size()-1; // excluding first elemtnt, which is count

		if (totalRead>=msgCount)
			break; // we read everything
	}
}

std::vector<CVKChat*> CVKMessageLoader::loadDialogList()
{
	vector<CVKChat*> list;
	return list;
}
CVKChat *CVKMessageLoader::loadSpecificChat(int id)
{
	CVKChat *chat=new CVKChat(id, false);
	loadHive(*chat, id, true);
	return chat;
}
CVKChat *CVKMessageLoader::loadSpecificDialog(int id)
{
	CVKChat *chat=new CVKChat(id, false);
	loadHive(*chat, id, false);
	return chat;
}
std::vector<CVKChat*> CVKMessageLoader::loadEverything()
{
	vector<CVKChat*> list;
	return list;
}