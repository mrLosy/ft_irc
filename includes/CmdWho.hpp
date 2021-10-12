#ifndef CMDWHO_HPP
#define CMDWHO_HPP

#include "Command.hpp"

class CmdWho : public Command
{
    public:
        CmdWho();
        ~CmdWho();
        void cmdRun();
        Client* getOperator(std::vector<Client*> clients);
};

#endif