#ifndef CMDAWAY_HPP
#define CMDAWAY_HPP

#include "Command.hpp"

class CmdAway : public Command
{
    public:
        CmdAway();
        ~CmdAway();
        void cmdRun();
        // class  IncorrectChannelName : public std::exception
		// {
		// 	const char* what() const throw();	
		// };
};

#endif