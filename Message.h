#pragma once
#include <string>

class Message
{
public:
	enum MessageType {
		outputMessage = 0x01,
		inputMessage = 0x02,
		gameActionMessage = 0x03
	};

	Message(const std::string load, int id, MessageType mType);
	~Message();

	const std::string& Read();
	int Write(const std::string load);
	int Append(const std::string load);
	MessageType GetType();
	int GetSource();

	

private:
	std::string payload;
	int connectionID;
	MessageType type;
};

