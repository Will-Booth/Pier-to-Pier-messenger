#pragma once
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>
#include <tchar.h>

class comms
{
public:
	comms() {};
	~comms() {};
	int port;
	int Initiation();
private:
	WSADATA wsaData;
	int wsaerr;
};

