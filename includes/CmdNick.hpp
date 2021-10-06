#ifndef CMDNICK_HPP
#define CMDNICK_HPP

#include "Command.hpp"

class CmdNick : public Command
{
    public:
        CmdNick();
        ~CmdNick();
        void cmdRun();

};

#endif