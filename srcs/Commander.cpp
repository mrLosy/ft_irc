#include "../includes/Commander.hpp"
#include "CmdHelp.hpp"
#include "CmdPass.hpp"
#include "CmdNick.hpp"
#include "CmdUser.hpp"
#include "CmdQuit.hpp"
#include "CmdJoin.hpp"
#include "CmdNotice.hpp"
#include "CmdPart.hpp"
#include "CmdInvite.hpp"
#include "CmdKick.hpp"
#include "CmdAway.hpp"
#include "CmdPrivmsg.hpp"
#include "CmdList.hpp"
#include "CmdNames.hpp"
#include "CmdWho.hpp"
#include "CmdTime.hpp"

using namespace std;

Commander::Commander(Server *server)
{
	_server = server;
	commands.push_back(new CmdHelp(commands));
	commands.push_back(new CmdPass());
	commands.push_back(new CmdNick());
	commands.push_back(new CmdUser());
	commands.push_back(new CmdQuit());
	commands.push_back(new CmdJoin());
	commands.push_back(new CmdNotice());
	commands.push_back(new CmdPart());
	commands.push_back(new CmdInvite());
	commands.push_back(new CmdKick());
	commands.push_back(new CmdPrivmsg());
	commands.push_back(new CmdAway());
	commands.push_back(new CmdList());
	commands.push_back(new CmdNames());
	commands.push_back(new CmdWho());
	commands.push_back(new CmdTime());
}

Commander::~Commander()
{
	for (vector<Command*>::const_iterator i = commands.begin(); i != commands.end(); ++i)
		delete *i;
}

void Commander::parse(Client *client, string msg)
{
	vector<string> arg = splitMsg(msg);
	_client = client;
	if (!arg.empty())
	{
		cout << "@" << _client->getNick() << " " << msg;
		for (vector<Command*>::const_iterator iterCmd = commands.begin(); iterCmd != commands.end(); ++iterCmd)
		{
			if (arg[0] == (*iterCmd)->getName())
			{
				(*iterCmd)->setClient(client);
				(*iterCmd)->setArgs(arg);
				(*iterCmd)->setServer(_server);
				try
				{
					(*iterCmd)->cmdRun();
				}
				catch(const exception& e)
				{
					cout << "'" + string(e.what()) + "'" << endl;
					client->sendMessageToClient(string(e.what()));
				}
				catch (const char* message)
				{
					string str = string(message);
					_client->sendMessageToClient(str);
				}
				catch(string message)
				{
					_client->sendMessageToClient(message);
				}
				break;
			}
		}
	}
}

vector<string> Commander::splitMsg(string msg)
{
	vector <string> elems;
	stringstream ss(msg);
	string item;
	while (getline(ss, item, ' '))
	{
		item.erase(std::remove(item.begin(), item.end(), '\n'), item.end());
		elems.push_back(item);
	}
	return elems;
}
