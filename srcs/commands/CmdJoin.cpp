#include "CmdJoin.hpp"
#include "Define.hpp"

CmdJoin::CmdJoin()
{
    _cmdName = "JOIN";
    _syntax = "JOIN <#channelname>";
    _cmdDescription = "Enters the channel. If there is no such channel, it creates one.";
}

CmdJoin::~CmdJoin()
{}

void CmdJoin::cmdRun()
{
    if (!_client->getRegistered())
        throw ERR_RESTRICTED;
    else if (_args.size() < 2)
        throw ERR_NEEDMOREPARAMS(_args[0]);
    else
    {
        if (!checkNameChannel(_args[1]))
            throw ERR_BADCHANMASK(_args[1]);
        Channel *channel = _server->getChannel(_args[1]);
        if (!channel)
        {
            _server->createChannel(_args[1]);
            channel = _server->getChannel(_args[1]);
            _client->setIsOperator(true);
            _client->sendMessageToClient(RPL_NOTOPIC(channel->getChannelName()));
        }
        if (channel->getClient(_client->getNick()))
            throw ERR_TOOMANYCHANNELS(_args[1]);
        channel->setClient(_client);
        channel->sendMessageToChannel(
            ":" + _client->getNick() + " JOIN #" + 
            channel->getChannelName() + "\r\n",
            _client->getNick()
        );
    }
}

bool CmdJoin::checkNameChannel(std::string name)
{
    if (name[0] != '#' && name[0] != '&')
        return false;
    return true;
}


