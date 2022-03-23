    ///////////////
	//		Server   //
///////////////

#include <iostream>
#include <WinSock2.h>
#include <vector>
#include <string>
#include <Windows.h>

using std::cout;
using std::endl;
using namespace std;

// For removing errors
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

// Count of clients
SOCKET Connections[2];

//!=========================================================

int main()
{
	cout << "Starting..." << endl;

	WSADATA wsaData;
	WORD DLLVersion = MAKEWORD(2, 2);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		cout << "Error !" << endl; exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	int port = 111;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	SOCKET sListen;
	sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	cout << "Success !" << endl;

	SOCKET newConnection;
	int countUsers = 0;

	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

	if (newConnection == 0)
		cout << "Error connection !" << endl;
	else
	{
		Connections[0] = newConnection;	countUsers++;
	}

	cout << "OK" << endl;

	//Save names
	char name1[10];
	char name2[10];
	recv(Connections[0], name1, sizeof(name1), NULL);		//##1
	cout << "User " << name1 << " connected !" << endl;
	recv(Connections[1], name2, sizeof(name2), NULL);		//##1
	cout << "User " << name2 << " connected !" << endl << endl;




	cout << endl << endl; system("pause"); return 0;
}