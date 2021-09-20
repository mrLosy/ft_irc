#pragma once

# include "Server.hpp"

class Server;

class Client {

private:
		int						_sockFd;
		int						_port;
		std::string				_id;
		std::string				_host;
		std::string				_nickname;
		std::string				_username;
		std::string				_firstname;
		std::string				_message;
		bool					_didEnter;
		bool					_isIdentified;

		static size_t		_maxChannels;
		// std::vector<Channel *>	_channels;
		// Channel*			_channel;

public:
		Client(int sockFd, int port, Server *serv, char *host = nullptr);
		~Client(void) {};

		std::string getId(void) {return _id;};
		bool		getIsIdentified(void) {return _isIdentified;};
		std::string getNick(void) {return _nickname;};
		int			getSockFd(void) {return _sockFd;};
		std::string	getHost(void) {return _host;};
		int			getPort(void) {return _port;};
		std::string getMessage(void) {return _message;};
		
		void		clearMessage(void);
		void		appendMessage(std::string message);
};