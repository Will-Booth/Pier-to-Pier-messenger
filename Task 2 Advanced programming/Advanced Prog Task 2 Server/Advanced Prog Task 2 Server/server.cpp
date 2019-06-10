#include "stdafx.h"
#include "server.h"


using namespace std;

server::server()
{
	//this assigns port with a value of 55555
	this ->port = 55555;
}


server::~server()
{
}

int server::ServerRun()
{
	//this creates a socket address
	SOCKADDR_STORAGE from;
	int retval, fromlen, socket_type;
	char servstr[NI_MAXSERV], hoststr[NI_MAXHOST];
	
	//error handling for if the socket and the address are wrong
	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
	{
		cout << "Error at socket(): " << WSAGetLastError() << endl;
		WSACleanup();
	}
	else
	{
		cout << "Socket() is OK!" << endl;
	}
	//binding the socket address and the socket take place here along with error handling
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	try 
	{
		bind(serverSocket, (SOCKADDR*)&service, sizeof(service));
		
	}
	catch (int error)
	{
		cout << "bind() failed: " << WSAGetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	cout << "bind() is OK!" << endl;
	// error handling for the server to listen on the socket awaiting a message
		try
		{
			listen(serverSocket, 1);
	    }
		catch(int error)
		{
			cout << "listen(): Error listening on socket " << WSAGetLastError() << endl;
		}
		cout << "listen() is OK, i'm waiting for connections..." << endl;

	fromlen = sizeof(socket_type);
	retval = getsockopt(serverSocket, SOL_SOCKET, SO_TYPE, (char *)&socket_type, &fromlen);
	fromlen = sizeof(from);
	//assigning accept socket with the socket address 
	acceptSocket = accept(serverSocket, (SOCKADDR *)&from, &fromlen);
	//error handling for if the socket isnt accepted 
	if (acceptSocket == INVALID_SOCKET)
	{
		cout << "accept failed: " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	//if the socket accepting is a success then it gives the name of the machine to the client
	retval = getnameinfo((SOCKADDR *)&from, fromlen, hoststr, NI_MAXHOST, servstr, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
	//error handling happens here in the case of the sendingof the machines information fails or succeeds
	if (retval != 0)
	{
		cout << "getnameinfo failed: " << retval << endl;
		WSACleanup();
		return -1;
	}
	cout << "Accepted connection from host " << hoststr << " and port " << servstr << endl;
	//boolean called quit
	bool quit = false;
	//while quit is false 
	while (!quit)
	{
		//sets bytecount to 200
		byteCount = recv(acceptSocket, receiveBuffer, 200, 0);
		//giving string a name and assigning recieve buffer to it
		string str(receiveBuffer);
		//string equal to the word quit
		if (str == "quit")
		{
			//set boolean quit to true
			quit = true;
		}
		//byte count is less than 0 error handle and exit
		if (byteCount < 0) {
			printf("Client: error %ld.\n", WSAGetLastError());
			return 0;
		}
		else 
		{
			//otherwise output data recieved
			printf("Received data : %s  \n", receiveBuffer);
			cout << receiveBuffer << endl;
		}
		//if quit is false 
		if (!quit)
		{
			//go to the sender function
			Sender();
		}
		
	}
	
	system("pause");
	WSACleanup();
	return 0;
}

int server::Sender()
{
	//error handling for the accept socket and socket address
	try
	{
		connect(acceptSocket, (SOCKADDR*)&service, sizeof(service));
	}
	catch(int error)
	{
		cout << "Client: connect() - Failed to connect." << endl;
		WSACleanup();
		return 0;
	}
	//output client has connected
		cout << "Client: connect() is OK!" << endl;
		cout << "Client: Can start sending and recieving data..." << endl;

	//askthe user to enter a message
	printf("Enter your message ");
	//buffer is 200 characters long
	cin.getline(buffer, 200);
	//bytecount is send, send is being passed acceptSocket, buffer along with the length of buffer
	byteCount = send(acceptSocket, buffer, 200, 0);
	//bytecount error handling
	if (byteCount == SOCKET_ERROR) {
		printf("Server send error %ld.\n", WSAGetLastError());
		return -1;
	}
	else {
		printf("Server: sent %ld bytes \n", byteCount);
	}
	
}



