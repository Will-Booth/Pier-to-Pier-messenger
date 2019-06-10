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
	//assigning clientSocket to INVALID_SOCKET
	clientSocket = INVALID_SOCKET;
	//clientSocket assigned to socket
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//if clientSocket is equal to INVALID_SOCKET
	if (clientSocket == INVALID_SOCKET)
	{
		//output error at socket
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	else
	{
		//output socket is OK
		cout << "socket() is OK!" << endl;
	}
	//sockaddr_in is assigned clientService
	sockaddr_in clientService;
	//clientService.sin_family assigned to AF_INET
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);
	//error handling for the connection of the client to the socket
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

	//boolean quit set to false
	bool quit = false;
	//while quit is false
	while (!quit)
	{
		//user to input message to send
		printf("Enter your message ");
		//add the buffer with the 200 character array
		cin.getline(buffer, 200);
		//string called str being passed buffer
		string str(buffer);
		//string str is equal to the word quit 
		if (str == "quit")
		{
			//set the boolean quit to true
			quit = true;
		}
		//bytecount is set to send, send is passed the clientsocket, buffer, 200(character amount for buffer), 0
		byteCount = send(clientSocket, buffer, 200, 0);
		//if bytecount is equalto SOCKET_ERROR
		if (byteCount == SOCKET_ERROR)
		{
			//output server send error
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
	//error handling for listening to the network
	try
	{
		(listen(clientSocket, 2));
	}
	catch (int error)
	{
		cout << "listen(): Error listening on socket " << WSAGetLastError() << endl;
	}
	cout << "listen() is OK, i'm waiting for connections..." << endl;
	//bytecount is assigned to recv, recv is passed clientsocket, recievebuffer, and the buffers character amount
	byteCount = recv(clientSocket, receiveBuffer, 200, 0);
	//if bytecount is less than 0
	if (byteCount < 0) {
		//output client error
		printf("Client: error %ld.\n", WSAGetLastError());
		//exit program
		return 0;
	}
	else {
		//output recieved data
		printf("Received data : %s  \n", receiveBuffer);
		//output the contents of the recieveBuffer
		cout << receiveBuffer << endl;
	}

}