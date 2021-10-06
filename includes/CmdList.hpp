#ifndef CMDLIST_HPP
#define CMDLIST_HPP

#include "Command.hpp"

class CmdList : public Command
{
    public:
        CmdList();
        ~CmdList();
        void cmdRun();
};

#endif