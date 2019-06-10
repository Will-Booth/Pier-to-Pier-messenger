#include "stdafx.h"
#include "server.h"


using namespace std;

server::server()
{
	this->port = 55555;
}


server::~server()
{
}

int server::ServerRun()
{
	SOCKADDR_STORAGE from;
	int retval, fromlen, socket_type;
	char servstr[NI_MAXSERV], hoststr[NI_MAXHOST];


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

	try
	{
		listen(serverSocket, 1);
	}
	catch (int error)
	{
		cout << "listen(): Error listening on socket " << WSAGetLastError() << endl;
	}
	cout << "listen() is OK, i'm waiting for connections..." << endl;

	fromlen = sizeof(socket_type);
	retval = getsockopt(serverSocket, SOL_SOCKET, SO_TYPE, (char *)&socket_type, &fromlen);
	fromlen = sizeof(from);
	acceptSocket = accept(serverSocket, (SOCKADDR *)&from, &fromlen);
	if (acceptSocket == INVALID_SOCKET)
	{
		cout << "accept failed: " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	retval = getnameinfo((SOCKADDR *)&from, fromlen, hoststr, NI_MAXHOST, servstr, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
	if (retval != 0)
	{
		cout << "getnameinfo failed: " << retval << endl;
		WSACleanup();
		return -1;
	}
	cout << "Accepted connection from host " << hoststr << " and port " << servstr << endl;

	bool quit = false;
	while (!quit)
	{

		byteCount = recv(acceptSocket, receiveBuffer, 200, 0);
		string str(receiveBuffer);
		if (str == "quit")
		{
			quit = true;
		}
		if (byteCount < 0) {
			printf("Client: error %ld.\n", WSAGetLastError());
			return 0;
		}
		else
		{
			printf("Received data : %s  \n", receiveBuffer);
			cout << receiveBuffer << endl;
		}
		if (!quit)
		{
			Sender();
		}

	}

	system("pause");
	WSACleanup();
	return 0;
}

int server::Sender()
{
	try
	{
		connect(acceptSocket, (SOCKADDR*)&service, sizeof(service));
	}
	catch (int error)
	{
		cout << "Client: connect() - Failed to connect." << endl;
		WSACleanup();
		return 0;
	}

	cout << "Client: connect() is OK!" << endl;
	cout << "Client: Can start sending and recieving data..." << endl;


	printf("Enter your message ");
	cin.getline(buffer, 200);
	byteCount = send(acceptSocket, buffer, 200, 0);
	if (byteCount == SOCKET_ERROR) {
		printf("Server send error %ld.\n", WSAGetLastError());
		return -1;
	}
	else {
		printf("Server: sent %ld bytes \n", byteCount);
	}

}



