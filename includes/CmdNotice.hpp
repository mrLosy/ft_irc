#ifndef CMDNOTICE_HPP
#define CMDNOTICE_HPP

#include "Command.hpp"

class CmdNotice : public Command
{
    public:
        CmdNotice();
        ~CmdNotice();
        void cmdRun();
};

#endif