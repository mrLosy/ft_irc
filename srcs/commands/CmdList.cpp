#include "CmdList.hpp"
#include "Define.hpp"

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
    if (!_client->getRegistered())
        throw ERR_RESTRICTED;
    else
    {
        std::vector<Channel*> channel = _server->getAllChannels();
        for (std::vector<Channel*>::const_iterator i = channel.begin(); i != channel.end(); i++)
        {
            _client->sendMessageToClient(RPL_LIST((*i)->getChannelName(), to_string((*i)->getClients().size())));
        }
        _client->sendMessageToClient(RPL_LISTEND);
    }
}