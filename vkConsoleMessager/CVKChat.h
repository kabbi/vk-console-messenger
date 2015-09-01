

#ifndef __C_VK_CHAT
#define __C_VK_CHAT

#include "CVKMessage.h"
#include <vector>

class CVKChat
{
protected:
	std::vector<CVKMessage*> messages;
	int chatId;
	// true - between two users
	bool dialog;
public:
	CVKChat(int chatId=0, bool isDialog=false)
		: chatId(chatId), dialog(dialog)
	{
	}
	~CVKChat()
	{
		clear();
	}

	void addMessage(CVKMessage *msg)
	{
		messages.push_back(msg);
	}
	CVKMessage *getMessage(int idx) const
	{
		return messages[idx];
	}
	int getMessageCount() const
	{
		return (int)messages.size();
	}

	int getChatId() {return chatId;}
	bool isDialog() {return dialog;}

	void clear()
	{
		for (int i=0; i<messages.size(); i++)
			delete messages[i];
		messages.clear();
	}
};

#endif