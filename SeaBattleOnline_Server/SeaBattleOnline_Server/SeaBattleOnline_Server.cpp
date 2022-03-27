  ///////////////
 //	  Server  //
///////////////

#include <iostream>
#include <WinSock2.h>

#include <Windows.h>
#include <ctime>

#include <vector>
#include <string>

using std::cout;
using std::endl;
using namespace std;

// For removing errors
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

// Count of clients
SOCKET Connections[2];

void sendIt(char msg[])
{
	send(Connections[0], msg, sizeof(msg), NULL);
	send(Connections[1], msg, sizeof(msg), NULL);
}

void recvIt(char msg[])
{
	recv(Connections[0], msg, sizeof(msg), NULL);
	recv(Connections[1], msg, sizeof(msg), NULL);
}

//!=========================================================

int main()
{
	SetConsoleTitle(L"Host - unready");

	srand(time(NULL));
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

	// Catch two users
	for (int i = 0; i < 2; ++i)
	{
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

		if (newConnection == 0)
			cout << "Error connection !" << endl;
		else
		{
			Connections[i] = newConnection;	countUsers++;
		}
	}

	cout << "OK" << endl;

	//Save names
	char name1[10];
	char name2[10];
	recv(Connections[0], name1, sizeof(name1), NULL);		//##1
	cout << "User " << name1 << " connected !" << endl;
	recv(Connections[1], name2, sizeof(name2), NULL);		//##1
	cout << "User " << name2 << " connected !" << endl << endl;

	SetConsoleTitle(L"Host - ready");
	char isItReady[1]{ '0' };

	// First
	int num01 = rand() % 2;
	char whoStartFirst[1];

	char firstUser[10];
	for (int i = 0; i < 10; ++i)
	{
		if (name1[i] == '\0')
		{
			firstUser[i] = '\0';
			break;
		}
		else
			firstUser[i] = name1[i];
	}
	//cout << name1 << " " << firstUser << endl;

	sendIt(firstUser);		//#1

	if (num01 == 0)
	{
		whoStartFirst[0] = '0';
		sendIt(whoStartFirst);		//#2
		cout << whoStartFirst[0] << endl;

		char cordXY[2];
		recvIt(cordXY);		//##2
	}
	else if (num01 == 1)
	{
		whoStartFirst[0] = '1';
		sendIt(whoStartFirst);		//#1
		cout << whoStartFirst[0] << endl;


	}
	else cout << "Error !" << endl;


	cout << endl << endl; system("pause"); return 0;
}