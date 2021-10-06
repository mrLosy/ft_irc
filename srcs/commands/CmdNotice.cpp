#include "CmdNotice.hpp"

CmdNotice::CmdNotice()
{
    _cmdName = "NOTICE";
    _syntax = "NOTICE <receiver> <message>";
    _cmdDescription = "Sends a message.";
}

CmdNotice::~CmdNotice()
{}

void CmdNotice::cmdRun()
{
    if (!_client->getEnterPassword())
        throw CmdNotice::NoPasswordEntered();
    else if (!_client->getRegistered())
        throw CmdNotice::NoRegistered();
    else if (_args.size() < 3)
        throw CmdNotice::InvalidNumOfArgs();
    else
    {
        std::string msg = createMsg();
        if (_args[1][0] == '#' || _args[1][0] == '&')
        {
            Channel *toChannel = _server->getChannel(_args[1]);
            if (!toChannel)
                throw CmdNotice::ChannelDoesNotExist();
            _client->sendMessageToClient("Message sending.\n");
            toChannel->sendMessageToChannel(msg);
        }
        else
        {
            Client *toClient = _server->getClient(_args[1]);
            if (!toClient)
                throw CmdNotice::UserDoesNotExist();
            _client->sendMessageToClient("Message sending.\n");
            toClient->sendMessageToClient(msg);
        }
    }
}

std::string CmdNotice::createMsg()
{
    std::string msg = _client->getNick() + ": ";
    for (size_t i = 2; i < _args.size(); i++)
    {
        msg = msg + _args[i];
        if (i + 1 != _args.size())
            msg += " ";
    }
    msg += "\n";
    return msg;
}