#include "Message.h"


Message::Message(const std::string load)
{
	payload = load;
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
