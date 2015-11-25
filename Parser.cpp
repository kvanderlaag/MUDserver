#include "Parser.h"
#include "Message.h"

#include <sstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <algorithm>
#include <iterator>
#include <cctype>

/**
* Parses a message from a connection
* Sends the parsed message to the correct function in the game world with the conenction id
* Returns a vector of messages to send back out to connections
*/
Message* Parser::Parse(const Message* mess) const
{
	// Input message
	if (mess->GetType() == 2) {

		Message* gameMessage = new Message("", mess->GetSource(), Message::MessageType::gameActionMessage);
		std::string buffer;
		std::stringstream iss(mess->Read());

		std::string command;

		std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss},
			std::istream_iterator<std::string>{} };

		command = tokens.front();
		tokens.erase(tokens.begin(), tokens.begin() + 1);
		std::cout << "Command: " << command << std::endl;

		for (int i = 0; i < command.length(); ++i) {
			command.at(i) = std::tolower(command.at(i));
		}

		for each (std::string token in tokens) {
			for (int i = 0; i < token.length(); ++i) {
				token.at(i) = std::tolower(token.at(i));
			}
			std::cout << token << std::endl;
		}


		if (command == "look")
		{
			//Look around room

		}
		else if (command == "move")
		{

		}
		else if (command == "say")
		{

		}
		else if (command == "take")
		{

		}
		else if (command == "help")
		{

		}
		else if (command == "signup")
		{

		}
		else if (command == "login")
		{

		}
		else if (command == "logout")
		{

		}
		else {
			//Return invalid command

		}

		gameMessage->Write("Balls.");

		return gameMessage;
	}
	// Game World Command Message
	else if (mess->GetType() == 1) {
		return nullptr;
	}
	// Output message
	else if (mess->GetType() == 3) {
		return nullptr;
	}

	return nullptr;
}
