#include "CmdNick.hpp"

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
    if (!_client->getEnterPassword())
        throw CmdNick::NoPasswordEntered();
    else if (_args.size() < 1)
        throw CmdNick::InvalidNumOfArgs();
    else if (_server->checkExistClient(_args[1]))
        throw CmdNick::ClientWithThisNickExists();
    else
    {
        _client->setNick(_args[1]);
        _client->sendMessageToClient(
            "You changed the nickname to \"" 
            + _client->getNick() + "\"\n"
        );
    }
}