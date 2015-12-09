#include "MessageBuffer.h"

#include <queue>
#include <iostream>

/**
* Create a message buffer
*/
MessageBuffer::MessageBuffer()
	: length(0)
{

}

/**
* Destroy the message buffer
*/
MessageBuffer::~MessageBuffer()
{
	std::cout << "Destroying message buffer.\n";
}

/**
* Place a message at the end of the message buffer
*/
int MessageBuffer::PutMessage(Message* mess)
{
	buffer.push(mess);
	return ++length;
}

/**
* Grab the next message in the message buffer
*/
Message* MessageBuffer::DequeueMessage()
{
	Message* ret = buffer.front();
	buffer.pop();
	length--;
	return ret;
}

/**
* Checks if the message buffer is empty
*/
bool MessageBuffer::IsEmpty()
{
	if (length == 0)
	{
		return true;
	}
	return false;
}