#include "CmdPrivmsg.hpp"

CmdPrivmsg::CmdPrivmsg()
{
    _cmdName = "PRIVMSG";
    _syntax = "PRIVMSG <receiver> <message>";
    _cmdDescription = "Sends a message.";
}

CmdPrivmsg::~CmdPrivmsg()
{}

void CmdPrivmsg::cmdRun()
{
    if (!_client->getEnterPassword())
        throw CmdPrivmsg::NoPasswordEntered();
    else if (!_client->getRegistered())
        throw CmdPrivmsg::NoRegistered();
    else if (_args.size() < 3)
        throw CmdPrivmsg::InvalidNumOfArgs();
    else
    {
        std::string msg = createMsg();
        if (_args[1][0] == '#' || _args[1][0] == '&')
        {
            Channel *toChannel = _server->getChannel(_args[1]);
            if (!toChannel)
                throw CmdPrivmsg::ChannelDoesNotExist();
            _client->sendMessageToClient("Message sending.\n");
            toChannel->sendMessageToChannel(msg);
        }
        else
        {
            Client *toClient = _server->getClient(_args[1]);
            if (!toClient)
                throw CmdPrivmsg::UserDoesNotExist();
            _client->sendMessageToClient("Message sending.\n");
            toClient->sendMessageToClient(msg);
            if (toClient->getAwayMessage().size() != 0)
            {
                std::string awayMsg;
                awayMsg = toClient->getNick() + "(away): " + toClient->getAwayMessage();
                _client->sendMessageToClient(awayMsg);
            }
        }
    }
}

std::string CmdPrivmsg::createMsg()
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