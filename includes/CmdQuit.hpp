#ifndef CMDQUIT_HPP
#define CMDQUIT_HPP

#include "Command.hpp"

class CmdQuit : public Command
{
    public:
        CmdQuit();
        ~CmdQuit();
        void cmdRun();
};

#endif 