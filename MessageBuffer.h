#pragma once

#include "Message.h"
#include <queue>

/**
* Header for message buffer class
*/
class MessageBuffer
{
public:
	MessageBuffer();
	~MessageBuffer();
	int PutMessage(Message* mess);
	Message* DequeueMessage();
	bool IsEmpty();

private:
	std::queue<Message*> buffer;
	int length;
};