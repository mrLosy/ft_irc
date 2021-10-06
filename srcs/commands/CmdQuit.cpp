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
	if (_args.size() > 1)
	{
		vector<string>::const_iterator i = _args.begin();
		i++;
		while (i != _args.end())
		{
			_client->sendMessageToClient(*i + " ");
			i++;
		}
	}
	_server->deleteClient(_client->getId());
}
