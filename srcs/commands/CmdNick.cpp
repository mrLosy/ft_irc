#include "CmdNick.hpp"
#include "Define.hpp"

using namespace std;

CmdNick::CmdNick()
{
    _cmdName = "NICK";
    _syntax = "Syntax: NICK <nickname>";
    _cmdDescription = "Allows the user to change his nickname in IRC.";
}

CmdNick::~CmdNick()
{}

void CmdNick::cmdRun()
{
    if (_args.size() != 2)
        throw ERR_NEEDMOREPARAMS(_args[0]);
    else if (_server->checkExistClient(_args[1]))
        throw ERR_NICKNAMEINUSE(_args[1]);
    else
    {
        _client->setNick(_args[1]);
        _client->sendMessageToClient(
            ":" + _client->getNick() + " " + "NICK " + _client->getNick() + "\r\n"
        );
        _client->registered();
    }
}