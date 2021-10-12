#include "CmdPrivmsg.hpp"
#include "Define.hpp"

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
    if (!_client->getRegistered())
        throw ERR_RESTRICTED;
    else if (_args.size() == 2)
        throw ERR_NOTEXTTOSEND;
    else if (_args.size() < 3)
        throw ERR_NEEDMOREPARAMS(_args[0]);
    else if (_client->getNick() == _args[1])
        throw ERR_TOOMANYTARGETS(_args[1]);
    else
    {
        std::string msg = createMsg();
        Channel *toChannel = _server->getChannel(_args[1]);
        if (toChannel != nullptr)
        {
            toChannel->sendMessageToChannel(":" + _client->getNick() + " PRIVMSG " + toChannel->getChannelName() + " : " + msg, _client->getNick());
        }
        else
        {
            Client *toClient = _server->getClient(_args[1]);
            if (!toClient)
                throw ERR_NOSUCHNICK(_args[1]);
            std::string toClientStr = toClient->getNick();
            toClient->sendMessageToClient(":" + _client->getNick() + " PRIVMSG " + toClientStr + ": " + msg + "\r\n");
            if (toClient->getAwayMessage().size() != 0)
            {
                throw RPL_AWAY(toClient->getNick(), toClient->getAwayMessage());
            }
        }
    }
}