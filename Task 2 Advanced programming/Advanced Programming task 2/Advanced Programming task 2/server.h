#pragma once
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>
#include <tchar.h>
#include "comms.h"
class server :
	public comms
{
public:
	server();
	~server();
	int ServerRun();
	int byteCount;
	SOCKET serverSocket, acceptSocket;
	int Sender();
	sockaddr_in service;
	char buffer[200] = "";
	char receiveBuffer[200] = "";
};

