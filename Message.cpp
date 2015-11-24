#include "Message.h"

/**
* Create a message
*/
Message::Message(const std::string load, int id, MessageType mType)
{
	payload = load;
	connectionID = id;
	type = mType;
}

/**
* Destroys a message
*/
Message::~Message()
{

}

/**
* Returns the payload of a message
*/
const std::string& Message::Read() const
{
	return payload;
}

/**
* Changes the payload of a message
*/
int Message::Write(const std::string load)
{
	payload = load;
	return 0;
}

/**
* Adds more onto the end of an existing payload
*/
int Message::Append(const std::string load)
{
	payload += load;
	return 0;
}

/**
* Returns the type of the message
*/
Message::MessageType Message::GetType() const
{
	return type;
}

/**
* Returns the connection ID of the player who sent the message
*/
int Message::GetSource() const {
	return connectionID;
}
