#include "Message.h"


Message::Message(const std::string load, int id, MessageType mType)	/*Create a message*/
{
	payload = load;
	connectionID = id;
	type = mType;
}


Message::~Message()
{

}

const std::string& Message::Read() {					/*Returns the payload of a message*/
	return payload;
}

int Message::Write(const std::string load) {				/*Changes the payload of a message*/
	payload = load;
	return 0;
}

int Message::Append(const std::string load) {				/*Add load to the end of the message*/
	payload += load;
	return 0;
}

Message::MessageType Message::GetType() {				/*Returns the typf oe message*/
	return type;
}

int Message::GetSource() {						/*Returns the connection ID of the player who made the message*/
	return connectionID;
}
