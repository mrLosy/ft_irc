#ifndef COMMANDER_HPP
#define COMMANDER_HPP

#include <sstream>
#include "Server.hpp"

#include "Command.hpp"

class Command;
class Client;
class Server;

class Commander
{
	private:
		std::vector<Command*>	commands;
		Client					*_client;
		Server					*_server;

	public:
		Commander(Server *server);
		~Commander();

		void parse(Client *client, std::string msg);
		std::vector<std::string> splitMsg(std::string msg);
};

#endif