#include "Command.hpp"
#include "Server.hpp"

using namespace std;

Command::Command() {}

Command::~Command() {}

void Command::setClient(Client *client)
{
	this->_client = client;
}

void Command::setArgs(std::vector<std::string> args)
{
    if (_args.size() > 0)
        _args.clear();
    
    for (vector<string>::const_iterator i = args.begin(); i != args.end(); ++i)
    {
        _args.push_back((*i));
    }
}

void Command::setServer(Server *server)
{
    this->_server = server;
}

string Command::createMsg()
{
    string msg = ":";
    for (size_t i = 2; i < _args.size(); i++)
    {
        msg = msg + _args[i];
        if (i + 1 != _args.size())
            msg += " ";
    }
    return msg;
}

const char* Command::InvalidNumOfArgs::what() const throw()
{
	return "Invalid number of arguments.!\r\n";
}

const char* Command::NoPasswordEntered::what() const throw()
{
    return "Enter the server password!\r\n";
}

const char* Command::ERR_RESTRICTED::what() const throw()
{
    return "484 * :Your connection is restricted!\r\n";
}

const char* Command::ClientWithThisNickExists::what() const throw()
{
    return "A user with this nickname exists!\r\n";
}

const char* Command::ClientWithThisNickRegistered::what() const throw()
{
    return "A user with this nickname registered!\r\n";
}

const char* Command::NickOrChannelNameError::what() const throw()
{
    return "error nick or channel not found\r\n";
}

const char* Command::ChannelDoesNotExist::what() const throw()
{
    return "The channel does not exist!\r\n";
}

const char* Command::ClientIsNotOperator::what() const throw()
{
    return "The client is not an operator!\r\n";
}