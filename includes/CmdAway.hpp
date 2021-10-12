#ifndef CMDAWAY_HPP
#define CMDAWAY_HPP

#include "Command.hpp"

class CmdAway : public Command
{
    public:
        CmdAway();
        ~CmdAway();
        void cmdRun();
        std::string createAway(); 
};

#endif