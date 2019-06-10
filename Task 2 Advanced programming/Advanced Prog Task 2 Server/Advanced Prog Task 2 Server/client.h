#pragma once
#include "comms.h"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>
#include <tchar.h>
class client :
	public comms
{
public:
	client();
	~client();
	int ClientRun();
	int Reciever();
	SOCKET clientSocket;
	int byteCount;
	char receiveBuffer[200] = "";
	char buffer[200] = "";
};

