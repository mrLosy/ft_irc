#ifndef CLIENT_HPP
#define CLIENT_HPP

# include "Server.hpp"

class Server;

class Client {

private:
		int						_sockFd;
		int						_port;
		std::string				_id; // del?
		std::string				_host;
		std::string				_nickname;
		std::string				_realname;
		std::string				_message;
		std::string				_awayMessage;
		
		bool					_enterPassword;
		bool					_registered;
		bool					_isOperator;

		// std::vector<Channel *>	_channels;
		// Channel*			_channel;

public:
		Client(int sockFd, int port, Server *serv, char *host = nullptr);
		~Client(void) {};

		std::string getId(void) {return _id;} // del?
		std::string getNick(void) {return _nickname;}
		int			getSockFd(void) {return _sockFd;}
		std::string	getHost(void) {return _host;}
		int			getPort(void) {return _port;}
		std::string getMessage(void) {return _message;}
		std::string getRealname(void) {return _realname;}
		std::string	getAwayMessage(void) {return _awayMessage;}
		bool		getEnterPassword(void) {return _enterPassword;}
		bool		getRegistered(void) {return _registered;}
		bool		getIsOperator(void) {return _isOperator;}

		void		setSockFd(int sock) {_sockFd = sock;}
		void		setPort(int port) {_port = port;}
		void		setId(std::string id) {_id = id;} // del?
		void		setHost(std::string host) {_host = host;}
		void		setNick(std::string nick) {_nickname = nick;}
		void		setRealname(std::string name) {_realname = name;}
		void		setAwayMessage(std::string message) {_awayMessage = message;}
		
		void		setEnterPassword(bool i) {_enterPassword = i;}
		void		setRegistered(bool i) {_registered = i;}
		void		setIsOperator(bool i) {_isOperator = i;}

		
		void		clearMessage(void);
		void		appendMessage(std::string message);
		void		sendMessageToClient(std::string message);
};

#endif