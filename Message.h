#pragma once
#include <string>

class Message
{
public:
	Message(const std::string load);
	~Message();

	const std::string& Read();
	int Write(const std::string load);
	int Append(const std::string load);

private:
	std::string payload;
};

