#include "CmdUser.hpp"

using namespace std;

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
    if (!_client->getEnterPassword())
        throw CmdUser::NoPasswordEntered();
    else if (_args.size() < 5)
        throw CmdUser::InvalidNumOfArgs();
    else if (_server->checkExistClient(_args[1]) && _server->getClient(_args[1])->getRegistered())
        throw CmdUser::ClientWithThisNickRegistered();
    else
    {
        _client->setNick(_args[1]);
        _client->setRealname(_args[4]);
        _client->setRegistered(1);
        string msgToClient = "User " + _client->getNick() + " is registered.\n";
        _client->sendMessageToClient(msgToClient);
    }
}