#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>

#include "Client.hpp"

class Client;
class Server;

class Command
{
	protected:
		std::string					_cmdName;
		std::string					_cmdDescription;
		std::string					_syntax;
		Client						*_client;
		Server						*_server;
		std::vector<std::string>	_args;
	
	public:
		Command();
		virtual ~Command();

		std::string 	getName() {return _cmdName;}
		std::string 	getDescription() {return _cmdDescription;}
		std::string 	getSyntax() {return _syntax;}
		void			setClient(Client *client);
		void			setArgs(std::vector<std::string> args);
		void			setServer(Server *server);
		virtual void	cmdRun() = 0;
		class InvalidNumOfArgs : public std::exception
		{
			const char* what() const throw();	
		};
		class NoPasswordEntered : public std::exception
		{
			const char* what() const throw();
		};
		class NoRegistered : public std::exception
		{
			const char* what() const throw();
		};
		class ClientWithThisNickExists : public std::exception
		{
			const char* what() const throw();
		};
		class ClientWithThisNickRegistered : public std::exception
		{
			const char* what() const throw();
		};
	    class   UserDoesNotExist : public std::exception
		{
			const char* what() const throw();	
		};
	    class ChannelDoesNotExist : public std::exception
		{
			const char* what() const throw();	
		};
		class ClientIsNotOperator : public std::exception
		{
			const char* what() const throw();
		};
};

#endif