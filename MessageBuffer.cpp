#include "MessageBuffer.h"

#include <queue>

MessageBuffer::MessageBuffer()
{
	length = 0;
}


MessageBuffer::~MessageBuffer()
{

}

int MessageBuffer::PutMessage(Message* mess) {
	buffer.push(mess);
	return ++length;
}

Message* MessageBuffer::DequeueMessage() {
	Message* ret = buffer.front();
	buffer.pop();
	length--;
	return ret;
}

bool MessageBuffer::IsEmpty() {
	if (length == 0) {
		return true;
	}
	return false;
}

