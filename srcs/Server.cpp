#include "../includes/Server.hpp"

using namespace std;

Server::Server(string host, string port, string pass) : _host(host), _port(port), _pass(pass) {
	stringstream stream;
	
	int portCheck = 0;
	stream << port;
	stream >> portCheck;

	if (portCheck < 1 || portCheck > 65535)
		Announcement::Fatal("The port number is invalid it must be between 1 and 65535 !");
	this->createSocket();
	for (int i = 0; i < 3; i++)
		_id[i] = 1;
}

int		Server::getId(int i){
	if (i < 0 || i > 2)
		Announcement::Fatal("Error: getId");
	if (_id[i] > 32)
		_id[i] = 1;
	_id[i]++;
	return (_id[i]);
}

Client *Server::getIdClient(string id) {
	for (vector<Client *>::iterator itClient = _clients.begin(); itClient != _clients.end(); itClient++)
	{
		string	_idClient = (*itClient)->getId();
		if (_idClient == id)
			return *itClient;
	}
	return nullptr;
}

void	Server::createSocket(void){
	addrinfo	hints;
	addrinfo	*servinfo;

	memset(&hints, 0, sizeof(hints));

	hints.ai_family   = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags    = AI_PASSIVE;
	if (getaddrinfo(_host.c_str(), _port.c_str(), &hints, &servinfo) != 0)
		Announcement::Fatal("Error: getaddrinfo");

	addrinfo	*p;
	int			sock;
	int			yes = 1;

	for (p = servinfo; p != nullptr; p = p->ai_next) {
		sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (sock == -1)
			continue;
		if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		{
			close(sock);
			freeaddrinfo(servinfo);
			Announcement::Fatal("Error: setsockopt");
		}
		if (bind(sock, p->ai_addr, p->ai_addrlen) == -1)
		{
			close(sock);
			continue;
		}
		break;
	}
	freeaddrinfo(servinfo);
	if (p == nullptr)
		Announcement::Fatal("Error: failed to find address");
	if (listen(sock, MAX_CONNECTION) == -1)
		Announcement::Fatal("Error: listen");

	_sock = sock;
}

void Server::start(void){
	pollfd	newPollfd = {_sock, POLLIN, 0};
	pollfd	ptrPollfd;

	_Commander = new Commander(this);
	if (fcntl(_sock, F_SETFL, O_NONBLOCK) == -1)
	 	Announcement::Fatal("Error: poll: fcntl");
	
	vector<pollfd>::iterator	iterPoll;
	_pollfds.push_back(newPollfd);



	cout << "Server created!" << endl;

	while (1)
	{
		iterPoll = _pollfds.begin();
		if (poll(&(*iterPoll), _pollfds.size(), -1) == -1)
			Announcement::Fatal("Error: poll");
		for (vector<pollfd>::iterator itPollfd = _pollfds.begin(); itPollfd != _pollfds.end(); itPollfd++)
		{
			ptrPollfd = *itPollfd;

			if ((ptrPollfd.revents & POLLHUP) == POLLHUP){
        	    vector<Client *>::iterator	itClient = _clients.begin();
        	    advance(itClient, distance(_pollfds.begin(), itPollfd) - 1);

				if (_clients.empty())
					break;
        	    cout << "disconnect not registered Client" << endl;
        	    this->deleteClient((*itClient)->getId());
        	    break;
        	}

			if ((ptrPollfd.revents & POLLIN) == POLLIN)
			{
				if (ptrPollfd.fd == _sock)
				{
					string str("Entered:\nPASS <password>\nNICK <nickname>\nUSER <username> <flags> <unused> <realname>\n\r");
						if (send(createClient(), str.c_str(), str.length(), 0) == -1)
							Announcement::Fatal("Error: send");
					break ;
				}
				else
				{
					vector<Client *>::iterator	itClient = _clients.begin();
					advance(itClient, distance(_pollfds.begin(), itPollfd) - 1);
					ssize_t byteRecv = recvMessage(*itClient); //del byteRecv ? 
					
					(void)byteRecv;
					
					// cout << (*itClient)->getMessage() << endl;
					_Commander->parse((*itClient), (*itClient)->getMessage());
				}
			}
		}
	}
}

int		Server::recvMessage(Client *client){
	ssize_t		byteRecved;
	char		message[100];

	client->clearMessage();
	memset(message, '\0', sizeof(message));
	while (!std::strstr(message, "\r\n"))
	{
		memset(message, '\0', sizeof(message));
		byteRecved = recv(client->getSockFd(), message, sizeof(message), 0);
		if (byteRecved <= 0)
			break ;
		client->appendMessage(message);
	}
	return (byteRecved);
}

void	Server::deleteClient(string id){
	int socketClient = this->getIdClient(id)->getSockFd();
	
	vector<pollfd>::iterator	it = _pollfds.begin();
	vector<pollfd>::iterator	itEnd = _pollfds.end();
	for (; it != itEnd; it++ )
	{
		if (socketClient == (*it).fd)
		{
			close((*it).fd);
			_pollfds.erase(it);
			break ;
		}
	}

	vector<Client *>::iterator	itC = _clients.begin();
	vector<Client *>::iterator	itEndC = _clients.end();
	for (; itC != itEndC; itC++ )
	{
		if ((*itC)->getId() == id)
		{
            delete (*itC);
            _clients.erase(itC);
            break ;
		}
	}
}

int		Server::createClient(void){
	int				client_d;
	sockaddr_in		client_addr;
	socklen_t		s_size;

	memset(&client_addr, 0, sizeof(client_addr));
	s_size = sizeof(client_addr);
	if ((client_d = accept(_sock, (sockaddr *) &client_addr, &s_size)) == -1)
		Announcement::Fatal("Error: accept");

	pollfd	newPollfd = {client_d, POLLIN, 0};
	_pollfds.push_back(newPollfd);
	if (fcntl(client_d, F_SETFL, O_NONBLOCK) == -1)
	 	Announcement::Fatal("Error: poll: fcntl");

	Client	*newClient = new Client(client_d, ntohs(client_addr.sin_port), this, inet_ntoa(client_addr.sin_addr));
	_clients.push_back(newClient);

	cout << "New client " << newClient->getNick() << "@" << newClient->getHost() << ":" << newClient->getPort() << endl;
	return client_d;
}

bool	Server::checkClientPass(string str)
{
	if (str != _pass)
		return 0;
	return 1;
}

void	Server::createChannel(string channelName)
{
	_channels.push_back(new Channel(channelName));
}

Client	*Server::getClient(string clientName)
{
	for (vector<Client*>::const_iterator i = _clients.begin(); i != _clients.end(); ++i)
	{
		if ((*i)->getNick() == clientName)
			return (*i);
	}
	return nullptr;
}

bool	Server::checkExistChannel(string channelName)
{
	for (vector<Channel*>::const_iterator i = _channels.begin(); i != _channels.end(); ++i)
	{
		if ((*i)->getChannelName() == channelName)
			return true;
	}
	return false;
}

bool	Server::checkExistClient(string clientName)
{
	for (vector<Client*>::const_iterator i = _clients.begin(); i != _clients.end(); ++i)
	{
		if ((*i)->getNick() == clientName)
			return true;
	}
	return false;
}

Channel	*Server::getChannel(string channelName)
{
	for (vector<Channel*>::const_iterator i = _channels.begin(); i != _channels.end(); ++i)
	{
		if ((*i)->getChannelName() == channelName)
			return (*i);
	}
	return nullptr;
}

vector<Channel*> Server::getAllChannels()
{
	return _channels;
}

vector<Client*>	Server::getAllClients()
{
	return _clients;
}