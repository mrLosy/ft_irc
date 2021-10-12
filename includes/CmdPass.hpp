#ifndef CMDPASS_HPP
#define CMDPASS_HPP

#include "Command.hpp"

class CmdPass : public Command
{
	public:
		CmdPass();
		~CmdPass();
		void cmdRun();
};

#endif