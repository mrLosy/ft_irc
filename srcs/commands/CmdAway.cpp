#include "CmdAway.hpp"
#include "Define.hpp"

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
    if (!_client->getRegistered())
        throw ERR_RESTRICTED;
    else
    {
        if (_args.size() > 2)
        {
            string awayMessage = createAway();
            _client->setAwayMessage(awayMessage);
            _client->sendMessageToClient(RPL_NOWAWAY);
        }
        else
        {
            if (_client->getAwayMessage().size() != 0)
            {
                _client->setAwayMessage("");
                _client->sendMessageToClient(RPL_UNAWAY);
            }
        }
    }
}

string  CmdAway::createAway()
{
    string away = "";
    for (size_t i = 1; i < _args.size(); i++)
    {
        away = away + _args[i];
        if (i + 1 != _args.size())
            away += " ";
    }
    return away;
}