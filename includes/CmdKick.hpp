#ifndef CMDKICK_HPP
#define CMDKICK_HPP

#include "Command.hpp"

class CmdKick : public Command
{
    public:
        CmdKick();
        ~CmdKick();
        void cmdRun();
};

#endif