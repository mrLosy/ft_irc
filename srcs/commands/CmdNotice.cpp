#include "CmdNotice.hpp"
#include "Define.hpp"

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
    if (!_client->getRegistered())
        throw ERR_RESTRICTED;
    else if (_args.size() == 1)
        throw ERR_NOTEXTTOSEND;
    else if (_args[1] == _args[2])
        throw ERR_TOOMANYTARGETS(_args[1]);
    else
    {
        string msg = createMsg();
        Channel *toChannel = _server->getChannel(_args[1]);
        if (toChannel != nullptr)
        {
            toChannel->sendMessageToChannel(":" + _client->getNick() + " NOTICE " + toChannel->getChannelName() + " " + msg, _client->getNick());
        }
        else
        {
            Client *toClient = _server->getClient(_args[1]);
            if (!toClient)
                throw ERR_NOSUCHNICK(_args[1]);
            string toClientStr = toClient->getNick(); 
            toClient->sendMessageToClient(":" + _client->getNick() + " NOTICE " + toClientStr + " " + msg + "\r\n");
        }
    }
}
