#include "CmdPass.hpp"
#include "Define.hpp"

CmdPass::CmdPass()
{
	_cmdName = "PASS";
	_syntax = "PASS <password>";
	_cmdDescription = "PASS <password>. Sets the connection password. This command must be used before registering a username.";
}

CmdPass::~CmdPass()
{}

void CmdPass::cmdRun()
{
	if (_args.size() < 2)
		throw ERR_NEEDMOREPARAMS(_args[0]);
	if (_client->getEnterPassword())
		throw ERR_ALREADYREGISTRED;
	else if (_server->getPass() != _args[1])
		throw ERR_PASSWDMISMATCH;
	else
	{
		_client->setEnterPassword(true);
		string nick = _client->getNick();
		_client->sendMessageToClient(":" + nick + " PASS Correct password\r\n");
		_client->registered();
	}
}