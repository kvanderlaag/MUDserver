#include "Parser.h"
#include "Message.h"

#include <sstream>

/**
* Parses a message from a connection
* Sends the parsed message to the correct function in the game world with the conenction id
* Returns a vector of messages to send back out to connections
*/
std::vector<Message*>* Parser::Parse(GameWorld* world, int connectionId, std::string input)
{

	std::string buffer;
	std::stringstream iss(input);

	std::string command;
	std::string words;
	iss >> command;
	std::getline(iss, words);

	//MIGHT NEED TO GET MOVED TO SERVER IF SERVER CALLS FUNCTIONS IN GAMEWORLD
	std::vector<Message*>* msg;// = new Message("hi", connection_id, Message::outputMessage);

	if (command == "look")
	{
	//Look around room

		std::stringstream wss(words);
		std::string entity;
		wss >> entity;

		if( entity.length() > 0 )
			msg = world->Look(connectionId, entity);
		else
			msg = world->Look(connectionId);
	}
	else if (command == "move")
	{
	//move to the room specified in input[1]. Check if a legitimate move

		std::stringstream wss(words);
		std::string exit;
		wss >> exit;

		msg = world->Move(connectionId, exit);
	}
	else if (command == "say")
	{
	//Output message to other players

		msg = world->Say(connectionId, words);
	}
	else if (command == "take")
	{
	//get the item described in the next argument

		std::stringstream wss(words);
		std::string entity;
		wss >> entity;

		msg = world->Take(connectionId, entity);
	}
	else if (command == "help")
	{
	//Give the player a list of commands
		msg = world->Help(connectionId);
	}
	else if (command == "signup")
	{
	//Log the player out, if possible

		std::stringstream wss(words);
		std::string username;
		std::string password;
		wss >> username;
		wss >> password;

		msg = world->SignUp(connectionId, username, password);
	}
	else if (command == "login")
	{
	//Log the player out, if possible

		std::stringstream wss(words);
		std::string username;
		std::string password;
		wss >> username;
		wss >> password;

		msg = world->LogIn(connectionId, username, password);
	}
	else if (command == "logout")
	{
	//Log the player out, if possible

		msg = world->LogOut(connectionId);
	}
	else {
	//Return invalid command

	}


	return msg;
}
