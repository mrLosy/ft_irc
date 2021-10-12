#include "CmdUser.hpp"
#include "Define.hpp"

CmdUser::CmdUser()
{
    _cmdName = "USER";
    _syntax = "USER <nickname> <flags> <unused> <realname>";
    _cmdDescription = "Sets the user name, real name, and connection flag.";
}

CmdUser::~CmdUser()
{}

void CmdUser::cmdRun()
{
    if (_args.size() < 5)
        throw ERR_NEEDMOREPARAMS(_args[0]);
    if (_client->getRegistered())
        throw ERR_ALREADYREGISTRED;
    else
    {
        _client->setNick(_args[1]);
        _client->setRealname(_args[4]);
        _client->registered();
    }
}