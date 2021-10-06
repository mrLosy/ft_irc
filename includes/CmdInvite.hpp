#ifndef CMDINVITE_HPP
#define CMDINVITE_HPP

#include "Command.hpp"

class CmdInvite : public Command
{
    public:
        CmdInvite();
        ~CmdInvite();
        void cmdRun();
};

#endif