#include "Message.h"


Message::Message(const std::string load, int id, MessageType mType)
{
	payload = load;
	connectionID = id;
	type = mType;
}


Message::~Message()
{

}

const std::string& Message::Read() {
	return payload;
}

int Message::Write(const std::string load) {
	payload = load;
	return 0;
}

int Message::Append(const std::string load) {
	payload += load;
	return 0;
}

Message::MessageType Message::GetType() {
	return type;
}

int Message::GetSource() {
	return connectionID;
}
