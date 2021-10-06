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
    // if (!_client->getEnterPassword())
    //     throw CmdPrivmsg::NoPasswordEntered();
    if (!_client->getRegistered())
        throw CmdPrivmsg::NoRegistered();
    else if (_args.size() < 3)
        throw CmdPrivmsg::InvalidNumOfArgs();
    else
    {
        std::string msg = createMsg();
        if (_args[1][0] == '#' || _args[1][0] == '&')
        {
            Client *toClient = _server->getClient(_args[1]);
            Channel *toChannel = _server->getChannel(_args[1]);
            if (!toChannel)
                throw CmdPrivmsg::ChannelDoesNotExist();
            std::string toClientStr = toClient->getNick();
            toChannel->sendMessageToChannel(":" + toClientStr + " PRIVMSG #" + toChannel->getChannelName() + msg + "\r\n");
        }
        else
        {
            Client *toClient = _server->getClient(_args[1]);
            if (!toClient)
                throw CmdPrivmsg::UserDoesNotExist();
            // _client->sendMessageToClient("Message sending.\n");
            std::string toClientStr = toClient->getNick();
            toClient->sendMessageToClient(":" + toClientStr + " PRIVMSG " + toClientStr + " :" + msg + "\r\n");
            // if (toClient->getAwayMessage().size() != 0)
            // {
            //     std::string awayMsg;
            //     awayMsg = toClient->getNick() + "(away): " + toClient->getAwayMessage();
            //     _client->sendMessageToClient(awayMsg);
            // }
        }
    }
}

std::string CmdPrivmsg::createMsg()
{
    std::string msg;
    for (size_t i = 2; i < _args.size(); i++)
    {
        msg = msg + _args[i];
        if (i + 1 != _args.size())
            msg += " ";
    }
    // msg += "\n";
    return msg;
}