// Advanced Prog Task 2 Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "client.h"
#include "server.h"
#include "comms.h"

#define ServerStuff 

//#define ClientStuff

int main()
{
	client* MyClient = new client();
	server* MyServer = new server();
	comms* MyComms = new comms();

	MyComms->Initiation();
#ifdef ClientStuff
	MyClient->ClientRun();
#endif
#ifdef ServerStuff
	MyServer->ServerRun();
#endif
	return 0;
}

