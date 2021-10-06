#include "CmdKick.hpp"

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
    if (!_client->getEnterPassword())
        throw CmdKick::NoPasswordEntered();
    else if (!_client->getRegistered())
        throw CmdKick::NoRegistered();
    else if (_args.size() != 3)
        throw CmdKick::InvalidNumOfArgs();
    else if (!_client->getIsOperator())
        throw CmdKick::ClientIsNotOperator();
    else
    {
        Channel *toChannel = _server->getChannel(_args[1]);
        if (!toChannel)
            throw CmdKick::ChannelDoesNotExist();
        Client *toClient = _server->getClient(_args[2]);
        if (!toClient)
            throw CmdKick::UserDoesNotExist();
        _client->sendMessageToClient(
            "You kick client: \"" + 
            toClient->getNick() +
            "\" from the channel: \"" +
            toChannel->getChannelName() +
            "\"\n"
        );
        toChannel->removeClient(toClient->getNick());
    }
}