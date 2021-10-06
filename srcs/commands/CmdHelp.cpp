#include "CmdHelp.hpp"

//made for nc in terminal

using namespace std;

CmdHelp::CmdHelp(vector<Command*> &cmds) : cmds(cmds)
{
	_cmdName = "HELP";
	_syntax = "HELP";
	_cmdDescription = "Output a list of available commands";
}

CmdHelp::~CmdHelp() {}


void CmdHelp::cmdRun()
{
	string message;
	for (vector<Command*>::const_iterator i = cmds.begin(); i != cmds.end(); ++i)
	{
		message = "Name cmd: " + (*i)->getName() + ", syntax: " + (*i)->getSyntax() + ", decription cmd: " + (*i)->getDescription() + "\n";
		_client->sendMessageToClient(message);
	}
}
