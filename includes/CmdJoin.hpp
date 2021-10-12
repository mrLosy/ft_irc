#ifndef CMDJOIN_HPP
#define CMDJOIN_HPP

#include "Command.hpp"

class CmdJoin : public Command
{
    public:
        CmdJoin();
        ~CmdJoin();
        void cmdRun();
        bool checkNameChannel(std::string name);
        
};

#endif
