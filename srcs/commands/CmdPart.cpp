#include "CmdPart.hpp"

CmdPart::CmdPart()
{
    _cmdName = "PART";
    _syntax = "PART <channelname>";
    _cmdDescription = "Removes the client from the channel";
}

CmdPart::~CmdPart()
{}

void CmdPart::cmdRun()
{
    if (!_client->getEnterPassword())
        throw CmdPart::NoPasswordEntered();
    else if (!_client->getRegistered())
        throw CmdPart::NoRegistered();
    else if (_args.size() != 2)
        throw CmdPart::InvalidNumOfArgs();
    else
    {
        Channel *channel = _server->getChannel(_args[1]);
        if (!channel)
            throw CmdPart::NoSuchChannelException();
        channel->removeClient(_client->getNick());
        channel->sendMessageToChannel(
            "Client " +
            _client->getNick() +
            " left channel " +
            channel->getChannelName() +
            "\n"
        );
        _client->sendMessageToClient(
            "You have left the channel: \"" + 
            channel->getChannelName() + "\"\n"
        );
    }
}

const char* CmdPart::NoSuchChannelException::what() const throw()
{
    return "No such channel!\n";
}