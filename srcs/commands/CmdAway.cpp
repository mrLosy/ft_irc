#include "CmdAway.hpp"

CmdAway::CmdAway()
{
    _cmdName = "AWAY";
    _syntax = "AWAY [<message>]";
    _cmdDescription = "Sets the autoresponder";
}

CmdAway::~CmdAway()
{}

void CmdAway::cmdRun()
{
    if (!_client->getEnterPassword())
        throw CmdAway::NoPasswordEntered();
    else if (!_client->getRegistered())
        throw CmdAway::NoRegistered();
    else
    {
        if (_args.size() == 2)
        {
            _client->setAwayMessage(_args[1] + '\n');
        }
        else
        {
            if (_client->getAwayMessage().size() != 0)
            {
                _client->setAwayMessage("");
            }
        }
    }
}