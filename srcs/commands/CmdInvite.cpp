#include "CmdInvite.hpp"

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
    if (!_client->getEnterPassword())
        throw CmdInvite::NoPasswordEntered();
    else if (!_client->getRegistered())
        throw CmdInvite::NoRegistered();
    else if (_args.size() != 3)
        throw CmdInvite::InvalidNumOfArgs();
    else if (!_client->getIsOperator())
        throw CmdInvite::ClientIsNotOperator();
    else
    {
        Client *toClient = _server->getClient(_args[1]);
        if (!toClient)
            throw CmdInvite::UserDoesNotExist();
        Channel *toChannel = _server->getChannel(_args[2]);
        if (!toChannel)
            throw CmdInvite::ChannelDoesNotExist();
        toClient->sendMessageToClient(
            ":" + _client->getNick() +
            " INVITE " + _args[1] +
            " " + _args[2] + "\n"
        );
    }
}