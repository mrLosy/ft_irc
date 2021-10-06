#ifndef CMDHELP_HPP
#define CMDHELP_HPP

#include "Command.hpp"

#include <vector>
#include <iostream>

class CmdHelp : public Command
{
	private:
		std::vector<Command*> &cmds;
	
	public:
		CmdHelp(std::vector<Command*> &cmds);
		~CmdHelp();
		void cmdRun();
};

#endif