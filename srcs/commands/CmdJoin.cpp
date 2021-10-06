#include "CmdJoin.hpp"

CmdJoin::CmdJoin()
{
    _cmdName = "JOIN";
    _syntax = "JOIN <#channelname>";
    _cmdDescription = "Enters the channel. If there is no such channel, it creates one.";
}

CmdJoin::~CmdJoin()
{}

void CmdJoin::cmdRun()
{
    // if (!_client->getEnterPassword())
    //     throw CmdJoin::NoPasswordEntered();
    if (!_client->getRegistered())
        throw CmdJoin::NoRegistered();
    else if (_args.size() != 2 && _args.size() != 3)
        throw CmdJoin::InvalidNumOfArgs();
    else if (!checkNameChannel(_args[1]))
        throw CmdJoin::IncorrectChannelName();
    else
    {
        if (!_server->checkExistChannel(_args[1]))
        {
            _server->createChannel(_args[1]);
            _client->setIsOperator(true);
        }
        Channel *channel = _server->getChannel(_args[1]);
        if (channel->checkExistClient(_client->getNick()))
            throw CmdJoin::AlreadyOnTheChannel();
        channel->setClient(_client);
        // channel->sendMessageToChannel(
        //     "User " + _client->getNick() +
        //     " join to " +
        //     channel->getChannelName() + "\r\n"
        // );
        channel->sendMessageToChannel(
            ":" + _client->getNick() + " " + "JOIN" + " " + channel->getChannelName()
        );
    }
}

bool CmdJoin::checkNameChannel(std::string name)
{
    if (name[0] != '#' && name[0] != '&')
        return false;
    return true;
}

const char *CmdJoin::IncorrectChannelName::what() const throw()
{
    return "Incorrect channel name!\r\n";
}
const char *CmdJoin::AlreadyOnTheChannel::what() const throw()
{
    return "you are already on the channel!\r\n";
}

