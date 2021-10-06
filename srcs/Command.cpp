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

const char* Command::InvalidNumOfArgs::what() const throw()
{
	return "Invalid number of arguments.!\n";
}

const char* Command::NoPasswordEntered::what() const throw()
{
    return "Enter the server password!\n";
}

const char* Command::NoRegistered::what() const throw()
{
    return "User not registered!\n";
}

const char* Command::ClientWithThisNickExists::what() const throw()
{
    return "A user with this nickname exists!\n";
}

const char* Command::ClientWithThisNickRegistered::what() const throw()
{
    return "A user with this nickname registered!\n";
}

const char* Command::UserDoesNotExist::what() const throw()
{
    return "The user does not exist!\n";
}

const char* Command::ChannelDoesNotExist::what() const throw()
{
    return "The channel does not exist!\n";
}

const char* Command::ClientIsNotOperator::what() const throw()
{
    return "The client is not an operator!\n";
}