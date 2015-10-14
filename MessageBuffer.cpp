#include "MessageBuffer.h"

#include <queue>

MessageBuffer::MessageBuffer()
	: length(0)
{

}


MessageBuffer::~MessageBuffer()
{

}

int MessageBuffer::PutMessage(const Message& mess) {
	buffer.push((Message*) &mess);
	return ++length;
}

const Message* MessageBuffer::DequeueMessage() {
	const Message* ret = buffer.front();
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

