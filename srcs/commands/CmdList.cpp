#include "CmdList.hpp"

CmdList::CmdList()
{
    _cmdName = "LIST";
    _syntax = "LIST";
    _cmdDescription = "shows a list of available channels on the server";
}

CmdList::~CmdList()
{}

void CmdList::cmdRun()
{
    if (!_client->getEnterPassword())
        throw CmdList::NoPasswordEntered();
    else if (!_client->getRegistered())
        throw CmdList::NoRegistered();
    else
    {
        std::vector<Channel*> channel = _server->getAllChannels();
        for (std::vector<Channel*>::const_iterator i = channel.begin(); i != channel.end(); ++i)
        {
            _client->sendMessageToClient((*i)->getChannelName() + " ");
        }
        _client->sendMessageToClient("\n");
    }
}