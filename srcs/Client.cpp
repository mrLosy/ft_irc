#include "../includes/Client.hpp"

using namespace std;

Client::Client(int sockFd, int port, Server *serv, char *host) : _sockFd(sockFd), _port(port), _host(host){
	_nickname = "unknown";
	_isOperator = false;
	_awayMessage = "";
	// _channel = nullptr;
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