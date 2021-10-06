#include "CmdNames.hpp"

CmdNames::CmdNames()
{
    _cmdName = "NAMES";
    _syntax = "NAMES [<#channel>]";
    _cmdDescription = "List of users on the channel or all users and channels on server.";
}

CmdNames::~CmdNames()
{}

void CmdNames::cmdRun()
{
    if (!_client->getEnterPassword())
        throw CmdNames::NoPasswordEntered();
    else if (!_client->getRegistered())
        throw CmdNames::NoRegistered();
    else if (_args.size() > 2)
        throw CmdNames::InvalidNumOfArgs();
    else
    {
        if (_args.size() == 2)
        {
            Channel *channel = _server->getChannel(_args[1]);
            if (!channel)
                throw CmdNames::ChannelDoesNotExist();
            std::vector<Client*> clients = channel->getClients();
            for (std::vector<Client*>::const_iterator i = clients.begin(); i != clients.end(); ++i)
            {
                _client->sendMessageToClient((*i)->getNick() + " ");
            }
            _client->sendMessageToClient("\n");
        }
        else
        {
            std::vector<Channel*> channel = _server->getAllChannels();
            for (std::vector<Channel*>::const_iterator i = channel.begin(); i != channel.end(); ++i)
            {
                _client->sendMessageToClient((*i)->getChannelName() + " ");
            }
            std::vector<Client*> clients = _server->getAllClients();
            for (std::vector<Client*>::const_iterator iterClients = clients.begin(); iterClients != clients.end(); ++iterClients)
            {
                _client->sendMessageToClient((*iterClients)->getNick() + " ");
            }
            _client->sendMessageToClient("\n");
        }
    }
}