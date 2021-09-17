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
}

Server::~Server(void) {}

void	Server::createSocket(void){
	addrinfo	hints;
	addrinfo	*servinfo;

	memset(&hints, 0, sizeof(hints));

	hints.ai_family   = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags    = AI_PASSIVE;
	if (getaddrinfo(_host.c_str(), _port.c_str(), &hints, &servinfo) != 0)
		throw runtime_error("error: getaddrinfo");

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
			throw runtime_error("error: setsockopt");
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
		throw runtime_error("error: failed to find address");
	if (listen(sock, MAX_CONNECTION) == -1)
		throw runtime_error("error: listen");

	_sock = sock;
}

void Server::start(void){
	pollfd	newPollfd = {_sock, POLLIN, 0};
	if (fcntl(_sock, F_SETFL, O_NONBLOCK) == -1)
	 	throw runtime_error("Error: poll: fcntl");
	
	vector<pollfd>::iterator	iterPoll;
	_pollFds.push_back(newPollfd);

	cout << "Server created!" << endl;

	while (1 == 1){
		iterPoll = _pollFds.begin();
		if (poll(&(*iterPoll), _pollFds.size(), -1) == -1)
			throw std::runtime_error("Error: poll");
	}
}