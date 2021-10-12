#ifndef CMDTIME_HPP
#define CMDTIME_HPP

#include "Command.hpp"

class CmdTime : public Command
{
	public:
		CmdTime();
		~CmdTime();
		void cmdRun();
};

#endif