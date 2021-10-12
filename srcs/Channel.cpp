#include "Channel.hpp"

Channel::Channel(std::string name)
{
    _channelName = name;
}

Channel::~Channel()
{}

void    Channel::setClient(Client *client)
{
    _clients.push_back(client);
}

void    Channel::sendMessageToChannel(std::string message, std::string nickname)
{
    for (std::vector<Client*>::const_iterator i = _clients.begin(); i != _clients.end(); ++i)
    {
        if ((*i)->getNick() != nickname)
            (*i)->sendMessageToClient(message + "\r\n");
    }
}

void    Channel::removeClient(std::string clientName)
{
    int index = 0;
    for (std::vector<Client*>::const_iterator i = _clients.begin(); i != _clients.end(); ++i)
    {
        if ((*i)->getNick() == clientName)
            break;
        index++;
    }
    _clients.erase(_clients.begin() + index);
}

bool    Channel::checkExistClient(std::string clientName)
{
    for (std::vector<Client*>::const_iterator i = _clients.begin(); i != _clients.end(); ++i)
    {
        if ((*i)->getNick() == clientName)
            return true;
    }
    return false;
}

Client  *Channel::getClient(std::string clientName)
{
    for (std::vector<Client*>::const_iterator i = _clients.begin(); i != _clients.end(); ++i)
    {
        if ((*i)->getNick() == clientName)
            return (*i);
    }
    return nullptr;
}