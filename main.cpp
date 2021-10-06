#include "includes/Server.hpp"

using namespace std;

int main(int argc, char **argv){
	
	if (argc < 2 || argc > 3)
            Announcement::Fatal("Error: Usage: irc [host:port:password] <port> <password>");
        if (argc == 3)
        {
            Server ircserv("127.0.0.1", argv[1], argv[2]);
            ircserv.start();
        }
        else
        {
            vector<std::string> result;
            stringstream ss(argv[1]);
            string token;

            while (getline(ss, token, ':'))
                if (!token.empty())
                    result.push_back(token);

            if (result.size() != 3)
                Announcement::Fatal("Error: usage: ircs [host:port:password] <port> <password>");
            Server irc(result[0], result[1], result[2]);
            irc.start();
        }
	
	return (0);
}
//10.21.34.16