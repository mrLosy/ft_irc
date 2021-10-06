#ifndef SERVER_HPP
#define SERVER_HPP

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

# include "Announcement.hpp"
# include "Client.hpp"
# include "Commander.hpp"
# include "Channel.hpp"

# define MAX_CONNECTION	1024
# define LOCALHOST "127.0.0.1"

class Client;
class Commander;
class Channel;

class Server{

private:
		const std::string		_host;
		const std::string		_port;
		const std::string		_pass;
		int						_sock;
		std::vector<pollfd>		_pollfds;
		std::vector<Client *>	_clients;
		std::vector<Channel *>	_channels;
		int						_id[3];

		Commander				*_Commander;

public:
		Server(const std::string host, const std::string port, const std::string pass);
		~Server(void) {};

		int	getId(int i);
		Client *getIdClient(std::string id);

		void					createSocket(void);
		void					start(void);
		void					deleteClient(std::string id);
		int						createClient(void);
		int						recvMessage(Client *client);
		bool					checkClientPass(std::string str);
		void					createChannel(std::string channelName);
		bool					checkExistChannel(std::string channelName);
		bool					checkExistClient(std::string clientNickname);
		Client					*getClient(std::string clientName);
		Channel					*getChannel(std::string channelName);
		std::vector<Channel*>	getAllChannels();
		std::vector<Client*>	getAllClients();
};

#endif