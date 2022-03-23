
// Client //

/*
*
*       _____                _           _    _              __  __             _ ______        _
*      / ____|              | |         | |  | |            |  \/  |           (_)  ____|      | |  
*     | |     _ __ ___  __ _| |_ ___  __| |  | |__  _   _   | \  / | __ _ _ __  _| |__ __ _ ___| |_ 
*     | |    | '__/ _ \/ _` | __/ _ \/ _` |  | '_ \| | | |  | |\/| |/ _` | '_ \| |  __/ _` / __| __|
*     | |____| | |  __/ (_| | ||  __/ (_| |  | |_) | |_| |  | |  | | (_| | | | | | | | (_| \__ \ |_ 
*      \_____|_|  \___|\__,_|\__\___|\__,_|  |_.__/ \__, |  |_|  |_|\__,_|_| |_|_|_|  \__,_|___/\__|
*                                                    __/ |                                          
*                                                   |___/                                           
* 
* Sea Battle Online Game
* Proggram was downloading from https://github.com/Stas-inside/SeaBattle-Online, read more or subscribe on YT if you are interesting.
* Thanks to Me)
* 
* You may using extension in vs which needed for convenience(comfortable):
* Better Comments (by Omar Rwemi)
* Discord Rich Presence
* Claudia IDE
* 
*	Resources wich I used (Press Ctrl+click):
*	https://www.asciitable.com/
*	https://www.youtube.com/watch?v=WRhLWVrXxW8
* https://patorjk.com/
* 
* 
* 
* ---
* 
* Apache License 2.0:
* 
* Copyright 2022 Stas
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
* 		http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <iostream>
#include <WinSock2.h>

#include <Windows.h>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using namespace std;

// For removing errors
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

SOCKET Connection;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);		// For color nessassery

//----------------------------------------------------------------------------

void printFieldUser(vector<char> vec, const int SIZE, char letters[])
{
	cout << "* ";
	SetConsoleTextAttribute(hConsole, 240);		// ForeGround

	for (int i = 1; i < 10; ++i)
	{
		cout << i << " ";
	}
	cout << "10" << "\033[0m";

	for (int i = 0; i < SIZE; i++)
	{

		if (i == 0)		// Print left letter ("A" in start)
		{
			cout << endl;
			SetConsoleTextAttribute(hConsole, 240);
			cout << letters[0] << " " << "\033[0m";
		}
		else if (i % 10 == 0)	// Print letter after numbers that are divisible by 10 (10-20-30...)
		{
			cout << endl;
			SetConsoleTextAttribute(hConsole, 240);
			cout << letters[i / 10] << " ";		// If that true, print first digit of array (by /10) 1-B 2-C etc.
		}

		SetConsoleTextAttribute(hConsole, 3);		// Color
		cout << vec[i] << " " << "\033[0m";
	}
}

void printField(vector<char> vecMy, vector<char> vecEnemy, const int SIZE, char letters[])
{
	system("cls");
	cout << endl << endl << endl << "* ";
	SetConsoleTextAttribute(hConsole, 240);
	cout << "1 2 3 4 5 6 7 8 9 10\033[0m|  ";
	cout << "* ";
	SetConsoleTextAttribute(hConsole, 240);
	cout << "1 2 3 4 5 6 7 8 9 10\033[0m|" << endl;

	// Indexes of vectors	(Global)
	int indexOf1 = 0;
	int indexOf2 = 0;

	// 10 columns on vertical
	for (int i = 0; i < 10; ++i)
	{
		//#// First user
		// Print first lettrs at the left
		SetConsoleTextAttribute(hConsole, 240);
		cout << letters[i] << " \033[0m";

		// Do this for only 10 elements of cordMy elements
		for (int j = 0; j < 10; ++j)
		{
			SetConsoleTextAttribute(hConsole, 3);
			// Print indexes 0 1..9, thats why I have created globas indexes (13 str. upper)
			cout << vecMy[indexOf1] << " ";
			indexOf1++;
		}

		//// Indent (space between)
		//! DONT FORGET!!! we move each string and then when string ended '|' we move on new string
		cout << "\033[0m|  ";

		//#// Second user
		// Print first lettrs at the left
		SetConsoleTextAttribute(hConsole, 240);
		cout << letters[i] << " \033[0m";

		// Print only 10 elements of cordEnemy elements
		for (int j = 0; j < 10; ++j)
		{
			SetConsoleTextAttribute(hConsole, 3);
			// Print indexes 0 1..9, thats why I have created globas indexes
			cout << vecEnemy[indexOf2] << " ";
			indexOf2++;
		}
		cout << "\033[0m|" << endl;
	}
		
	cout << endl;
}

//----------------------------------------------------------

char letters[]{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

//!=========================================================

int main()
{
	cout << "Starting..." << endl;

	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 2);
	if (!WSAStartup(DLLVersion, &wsaData))
	{
		cout << "Error !" << endl;
	}
	cout << "Starting..." << endl;

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	int port = 111;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	
	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		cout << "Error: failed connct to server." << endl;
		exit(1);
	}

	cout << "Connected ! " << endl << endl;

	//# Begin

	int vectorSIZE = 100;
	vector<char> cordMy(vectorSIZE);
	vector<char> cordEnemy(vectorSIZE);

	// Fill vector
	for (int i = 0; i < vectorSIZE; i++)
	{
		// Space
		cordMy[i] = 32;	
		cordEnemy[i] = 32;

		cordMy[i] = '1';
		cordEnemy[i] = '2';
	}

	// Input
	cout << "Enter your name: ";
	char name[10];
	cin >> name;
	send(Connection, name, sizeof(name), NULL);		//#1

	printField(cordMy, cordEnemy, vectorSIZE, letters);



	cout << endl << endl; system("pause"); return 0;
}