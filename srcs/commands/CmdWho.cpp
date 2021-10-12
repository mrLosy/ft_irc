#include "CmdWho.hpp"
#include "Define.hpp"

CmdWho::CmdWho()
{
    _cmdName = "WHO";
    _syntax = "WHO <#channel>";
    _cmdDescription = "List users on channel";
}

CmdWho::~CmdWho()
{}

void CmdWho::cmdRun()
{
    if (!_client->getRegistered())
        throw ERR_RESTRICTED;
    else if (_args.size() < 2)
        throw ERR_NEEDMOREPARAMS(_args[0]);
    else
    {
        Channel *toChannel = _server->getChannel(_args[1]);
        if (!toChannel)
            throw ERR_NOSUCHCHANNEL(_args[1]);
        vector<Client*> clients = toChannel->getClients();
        _client->sendMessageToClient(RPL_WHOREPLY(toChannel->getChannelName(), to_string(clients.size()), getOperator(clients)->getNick()));
        _client->sendMessageToClient(RPL_ENDOFWHO);
    }
}

Client* CmdWho::getOperator(vector<Client*> clients)
{
    for (vector<Client*>::const_iterator i = clients.begin(); i != clients.end(); i++)
    {
        if ((*i)->getIsOperator())
            return (*i);
    }
    return nullptr;
}