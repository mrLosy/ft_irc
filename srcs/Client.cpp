#include "../includes/Client.hpp"

using namespace std;

Client::Client(int sockFd, int port, Server *serv, char *host) : _sockFd(sockFd), _port(port), _host(host){
	_nickname = "";
	_realname = "";
	_isOperator = false;
	_awayMessage = "";
	_enterPassword = false;
	_registered = false;
	_id = serv->getId(0) + serv->getId(1) + serv->getId(2);
}

void		Client::clearMessage(void){
	_message.clear();
}

void			Client::appendMessage(string message)
{
	_message.append(message);
	_message.erase(_message.find_last_not_of("\r\n") + 1);
	_message.append("\n");
}

void		Client::sendMessageToClient(std::string message)
{
	send(_sockFd, message.c_str(), message.length(), 0);
}

void		Client::registered()
{
	cout << getEnterPassword() << "|" << _nickname + "|" + _realname + "|" << endl; 
	if (getEnterPassword() && _nickname != "" && _realname != "")
	{
		std::string msg;
		sendMessageToClient(
			"001 * Welcome to the Internet Relay Network " +
			this->getNick() + "!" + this->getRealname() +
			"@" + this->getHost() + "\r\n"
		);
		_registered = true;
	}
}