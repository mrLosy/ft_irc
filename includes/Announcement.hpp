#ifndef ANNOUNCEMENT_HPP
#define ANNOUNCEMENT_HPP

#include <iostream>

#include <cerrno>
#include <cstdlib>
#include <cstring>

class Announcement{

private:
		Announcement() {};
public:
		~Announcement() {};

		static void Fatal(std::string str, int exitCode = 1);
};

#endif