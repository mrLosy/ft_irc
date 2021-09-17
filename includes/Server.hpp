#pragma once

# include <iostream>
# include <sstream>
# include <iomanip>
# include <string>
# include <stdexcept>
# include <vector>

# include <sys/socket.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <fcntl.h>
# include <unistd.h>
# include <poll.h>

#include "Announcement.hpp"

# define MAX_CONNECTION	1024
# define LOCALHOST "127.0.0.1"

class Server{

private:
		const std::string		_host;
		const std::string		_port;
		const std::string		_pass;
		int						_sock;
		std::vector<pollfd>		_pollFds;

public:
		Server(const std::string host, const std::string port, const std::string pass);
		~Server(void);

		void createSocket(void);
		void start(void);


};