#include "CmdQuit.hpp"

using namespace std;

CmdQuit::CmdQuit()
{
	_cmdName = "QUIT";
	_syntax = "QUIT [<quit message>]";
	_cmdDescription = "Disconnects the user from the server.";
}

CmdQuit::~CmdQuit()
{}

void CmdQuit::cmdRun()
{
	_server->deleteClient(_client->getId());
}
