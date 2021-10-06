#ifndef CMDNAMES_HPP
#define CMDNAMES_HPP

#include "Command.hpp"

class CmdNames : public Command
{
    public:
        CmdNames();
        ~CmdNames();
        void cmdRun();
};

#endif