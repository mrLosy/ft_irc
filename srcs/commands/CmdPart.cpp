#include "CmdPart.hpp"
#include "Define.hpp"

CmdPart::CmdPart()
{
    _cmdName = "PART";
    _syntax = "PART <channelname>";
    _cmdDescription = "Removes the client from the channel";
}

CmdPart::~CmdPart()
{}

void CmdPart::cmdRun()
{
    if (!_client->getRegistered())
        throw ERR_RESTRICTED;
    else if (_args.size() < 2)
        throw ERR_NEEDMOREPARAMS(_args[0]);
    else
    {
        Channel *channel = _server->getChannel(_args[1]);
        if (!channel)
            throw ERR_NOSUCHCHANNEL(_args[1]);
        if (!channel->getClient(_client->getNick()))
            throw ERR_NOTONCHANNEL(_args[1]);
        channel->removeClient(_client->getNick());
        channel->sendMessageToChannel(
            ":" + _client->getNick() +
            " " + "PART" + " #" +
            channel->getChannelName(),
            _client->getNick()
        );
    }
}
