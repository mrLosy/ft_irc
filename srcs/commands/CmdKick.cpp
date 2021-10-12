#include "CmdKick.hpp"
#include "Define.hpp"

CmdKick::CmdKick()
{
    _cmdName = "KICK";
    _syntax = "KICK <channel> <nickname>";
    _cmdDescription = "Kick client";
}

CmdKick::~CmdKick()
{}

void CmdKick::cmdRun()
{
    if (!_client->getRegistered())
        throw ERR_RESTRICTED;
    else if (_args.size() < 2)
        throw ERR_NEEDMOREPARAMS(_args[0]);
    else
    {
        Channel *toChannel = _server->getChannel("#" +  _args[1]);
        if (!toChannel)
            throw ERR_NOSUCHCHANNEL(_args[1]);
        if (!_client->getIsOperator())
            throw ERR_CHANOPRIVSNEEDED(_args[1]);
        if (!toChannel->getClient(_client->getNick()))
            throw ERR_NOTONCHANNEL(_args[1]);
        Client *toClient = _server->getClient(_args[2]);
        if (!toClient)
            throw ERR_USERNOTINCHANNEL(_args[2], _args[1]);
        toChannel->sendMessageToChannel(
            ":" + toClient->getNick() + " " + "KICK #" + toChannel->getChannelName() + " : kicked " + toClient->getNick() + "\r\n", toClient->getNick()
        );
        toChannel->removeClient(toClient->getNick());
    }
}