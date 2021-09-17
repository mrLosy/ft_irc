#include "includes/Server.hpp"

using namespace std;

int main(int argc, char **argv){
	try{
		if (argc < 2 || argc > 3)
            throw std::runtime_error("Error in argv! Usage: irc [host:port:password] <port> <password>");
        if (argc == 3)
        {
            Server irc(LOCALHOST, argv[1], argv[2]);
            irc.start();
        }
	}
	catch (const exception &e){
		e.what();
	}
	return (0);
}