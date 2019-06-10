#include "stdafx.h"
#include "comms.h"

using namespace std;



int comms::Initiation()
{
	
	WORD wVersionRequested = MAKEWORD(2, 2);
	//assigning WSAStartup to wsaerr
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	//error handling for wsaerr 
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


