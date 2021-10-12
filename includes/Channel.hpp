#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Client.hpp"

class Channel
{
    private:
        std::vector<Client*> _clients;
        std::string			_channelName;
	
	public:
		Channel(std::string name);
		~Channel();
		std::string				getChannelName() {return _channelName;}
		std::vector<Client*>	getClients() {return _clients;}
		Client					*getClient(std::string clientName);
		bool					checkExistClient(std::string clientName);
		void					setClient(Client *client);
		void					sendMessageToChannel(std::string message, std::string nickname);
		void					removeClient(std::string clientName);
};

#endif