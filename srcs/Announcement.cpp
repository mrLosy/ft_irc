#include "../includes/Announcement.hpp"

using namespace std;

void Announcement::Fatal(std::string str, int exitCode){
	cerr << str << endl;
	exit(exitCode);
}