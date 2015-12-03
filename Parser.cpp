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
Message* Parser::Parse(Message* mess) const
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
#ifdef _DEBUG_FLAG
		std::cout << "Command: " << command << std::endl;
#endif

		for (std::size_t i = 0; i < command.length(); ++i) {
			command.at(i) = std::tolower(command.at(i));
		}

		if (command != "say" && command != "shout" && command != "whisper" && command != "signup" 
			&& command != "desc" && command != "description" && command != "tell" && command != "t"
			&& command != "password" && command != "login") {
			for (std::size_t j = 0; j < tokens.size(); ++j) {
				for (std::size_t i = 0; i < tokens.at(j).length(); ++i) {
					tokens.at(j).at(i) = std::tolower(tokens.at(j).at(i));
				}
#ifdef _DEBUG_FLAG
				std::cout << token << std::endl;
#endif
				}
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

		//gameMessage->Write("Balls.");
		gameMessage->Write(command);
		for (std::string token : tokens) {
			gameMessage->Append(" " + token);
		}

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
