#ifndef CMDPART_HPP
#define CMDPART_HPP

#include "Command.hpp"

class CmdPart : public Command
{
    public:
        CmdPart();
        ~CmdPart();
        void cmdRun();

        class  NoSuchChannelException : public std::exception
		{
			const char* what() const throw();	
		};
};

#endif