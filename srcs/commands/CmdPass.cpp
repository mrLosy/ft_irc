#include "CmdPass.hpp"

using namespace std;

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
	// if (_args.size() != 2)
	// 	throw CmdPass::InvalidNumOfArgs();
	// if (!_server->checkClientPass(_args[1]))
	// 	throw CmdPass::IncorrectPasswordException();
	// else
	// {
		_client->setEnterPassword(1);
		string nick = _client->getNick();
		_client->sendMessageToClient(":" + _server->getHost() + " PASS Correct password\r\n");
	// }
}

const char *CmdPass::IncorrectPasswordException::what() const throw()
{
	return "Incorrect password!\n";
}