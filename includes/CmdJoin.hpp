#ifndef CMDJOIN_HPP
#define CMDJOIN_HPP

#include "Command.hpp"

class CmdJoin : public Command
{
    public:
        CmdJoin();
        ~CmdJoin();
        void cmdRun();
        bool checkNameChannel(std::string name);

        class  IncorrectChannelName : public std::exception
		{
			const char* what() const throw();	
		};
        class  AlreadyOnTheChannel : public std::exception
		{
			const char* what() const throw();	
		};
        
};

#endif
