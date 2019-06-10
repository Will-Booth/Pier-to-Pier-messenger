#include "stdafx.h"
#include "client.h"


using namespace std;

client::client()
{
}


client::~client()
{
}

int client::ClientRun()
{
	
	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else
	{
		cout << "socket() is OK!" << endl;
	}
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);

	try
	{
		(connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)));
	}
	catch (int error)
	{
			cout << "Client: connect() - Failed to connect." << endl;
			WSACleanup();
			return 0;
	}
		cout << "Client: connect() is OK!" << endl;
		cout << "Client: Can start sending and recieving data..." << endl;

	bool quit = false;
	while (!quit)
	{
		
		printf("Enter your message ");
		cin.getline(buffer, 200);
		string str(buffer);
		if (str == "quit")
		{
			quit = true;
		}
		byteCount = send(clientSocket, buffer, 200, 0);
		if (byteCount == SOCKET_ERROR)
		{
			printf("Server send error %ld.\n", WSAGetLastError());
			return -1;
		}
		else
		{
			printf("Server: sent %ld bytes \n", byteCount);
		}
		if (!quit)
		{
			Reciever();
		}
		
	}
	WSACleanup();
	return 0;
}



	int client::Reciever()
	{
		try
		{
			(listen(clientSocket, 2));
		}
		catch(int error)
		{
			cout << "listen(): Error listening on socket " << WSAGetLastError() << endl;
		}
		cout << "listen() is OK, i'm waiting for connections..." << endl;
		
		byteCount = recv(clientSocket, receiveBuffer, 200, 0);
		if (byteCount < 0) {
			printf("Client: error %ld.\n", WSAGetLastError());
			return 0;
		}
		else {
			printf("Received data : %s  \n", receiveBuffer);
			cout << receiveBuffer << endl;
		}
		
	}
		