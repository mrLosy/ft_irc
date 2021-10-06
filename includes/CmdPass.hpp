#ifndef CMDPASS_HPP
#define CMDPASS_HPP

#include "Command.hpp"

class CmdPass : public Command
{
	public:
		CmdPass();
		~CmdPass();
		void cmdRun();

		class  IncorrectPasswordException : public std::exception
		{
			const char* what() const throw();	
		};
};

#endif