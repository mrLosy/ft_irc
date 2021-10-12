#ifndef CMDPRIVMSG_HPP
#define CMDPRIVMSG_HPP

#include "Command.hpp"

class CmdPrivmsg : public Command
{
    public:
        CmdPrivmsg();
        ~CmdPrivmsg();
        void cmdRun();
};

#endif