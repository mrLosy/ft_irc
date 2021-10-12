#include "CmdTime.hpp"
#include "Define.hpp"

#include <chrono>
#include <ctime> 

CmdTime::CmdTime()
{
	_cmdName = "TIME";
	_syntax = "TIME";
	_cmdDescription = "Shows the current time";
}

CmdTime::~CmdTime()
{}

void CmdTime::cmdRun()
{
	time_t	t = time(0);
	tm		*now = localtime(&t);
	string	strtime = "";
	strtime += to_string(now->tm_year + 1900) + "-" + 
		to_string(now->tm_mon + 1) + "-" + 
		to_string(now->tm_mday) + "_" +
		to_string(now->tm_hour) + ":" +
		to_string(now->tm_min) + ":" +
		to_string(now->tm_sec);
	throw RPL_TIME(strtime);
}