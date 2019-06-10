#include "stdafx.h"
#include "comms.h"

using namespace std;

comms::comms()
{
	port = 55555;
}

int comms::Initiation()
{
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0)
	{
		cout << "The Winsock dll was not found!" << endl;
		return 0;
	}
	else
	{
		cout << "The Winsock dll was found!" << endl;
		cout << "The status: " << wsaData.szSystemStatus << endl;
	}
}

comms::~comms()
{
}
