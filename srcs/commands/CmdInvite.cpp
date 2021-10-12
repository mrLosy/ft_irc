#include "CmdInvite.hpp"
#include "Define.hpp"

CmdInvite::CmdInvite()
{
    _cmdName = "INVITE";
    _syntax = "INVITE <nickname> <channel>";
    _cmdDescription = "Invites the user to the channel";
}

CmdInvite::~CmdInvite()
{}

void CmdInvite::cmdRun()
{
    if (!_client->getRegistered())
        throw ERR_RESTRICTED;
    else if (_args.size() != 3)
        throw ERR_NEEDMOREPARAMS(_args[0]);
    else if (!_client->getIsOperator())
        throw ERR_CHANOPRIVSNEEDED(_args[2]);
    else
    {
        Channel *toChannel = _server->getChannel(_args[2]);
        if (!toChannel)
            throw ERR_NOSUCHCHANNEL(_args[2]);
        if (!toChannel->getClient(_client->getNick()))
            throw ERR_NOTONCHANNEL(toChannel->getChannelName());
        Client *toClient = _server->getClient(_args[1]);
        if (!toClient)
            throw ERR_NOSUCHNICK(_args[1]);
        if (toChannel->getClient(toClient->getNick()))
            throw ERR_USERONCHANNEL(toClient->getNick(), toChannel->getChannelName());
        toClient->sendMessageToClient(
            ":" + _client->getNick() +
            " INVITE " + _args[1] +
            " " + _args[2] + "\r\n"
        );
    }
}