

#ifndef __C_VK_MESSAGE_LOADER
#define __C_VK_MESSAGE_LOADER

#include "CVKMethodCaller.h"
#include "CVKChat.h"

class CVKMessageLoader
{
protected:
	CVKMethodCaller *caller;
    CLogManager log;

	void loadHive(CVKChat &chat, int id, bool dialog);
public:
	CVKMessageLoader(CVKMethodCaller *caller);
	~CVKMessageLoader();

	std::vector<CVKChat*> loadDialogList();
	CVKChat *loadSpecificChat(int id);
	CVKChat *loadSpecificDialog(int id);
	std::vector<CVKChat*> loadEverything();
};

#endif