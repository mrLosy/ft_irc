#ifndef CMDUSER_HPP
#define CMDUSER_HPP

#include "Command.hpp"

class CmdUser : public Command
{
    public:
        CmdUser();
        ~CmdUser();
        void cmdRun();

};

#endif