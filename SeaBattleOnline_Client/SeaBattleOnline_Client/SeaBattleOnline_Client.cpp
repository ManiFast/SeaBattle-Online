
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
#include <conio.h>
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

const int vectorSIZE = 100;

//----------------------------------------------------------------------------

void Gotoxy(short x, short y)
{
	SetConsoleCursorPosition(hConsole, { x,y });
}

// Skip this
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
	//system("cls");
	Gotoxy(0, 0);
	cout << endl << endl << "My ships:\t\t Enemy ships:" << endl << endl << "* ";
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

void sendIt(char msg[])
{
	send(Connection, msg, sizeof(msg), NULL);
}

void recvIt(char msg[])
{
	recv(Connection, msg, sizeof(msg), NULL);
}

//Disappear cusrsor
void CursorVisible(bool show)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hConsole, &structCursorInfo);
	structCursorInfo.bVisible = show;
	SetConsoleCursorInfo(hConsole, &structCursorInfo);
}


int CordinatesToXY(char cord1, char cord2)
{
	int numberXY = 0;
	int secondNumber = (int)cord2 - 48;		// 48 is the remainder that must be subtracted from (char) to get the number | это остаток который надо отнять от (чара) чтобы получить число

	//// A = 0 B = 10... and then plus second number
	// For ex. C6 => C = 20, 20+6=26 it xy for field
	switch (cord1)
	{
	case 'A':
		numberXY += 0;
		break;
	case 'B':
		numberXY += 10;
		break;
	case 'C':
		numberXY += 20;
		break;
	case 'D':
		numberXY += 30;
		break;
	case 'E':
		numberXY += 40;
		break;
	case 'F':
		numberXY += 50;
		break;
	case 'G':
		numberXY += 60;
		break;
	case 'H':
		numberXY += 70;
		break;
	case 'I':
		numberXY += 80;
		break;
	case 'J':
		numberXY += 90;
		break;

	default:
		//numberXY = 0;
		//secondNumber = 0;
		break;
	}

	numberXY += secondNumber;
	numberXY--; // Because we started from 0 !

	//cout << numberXY << " " << secondNumber << endl;
	return numberXY;
}

int SetShipsCordinates(char onedeck1[2], vector<char> &cordMyF)
{
	int onedeck1XY = CordinatesToXY(onedeck1[0], onedeck1[1]);

	cordMyF[onedeck1XY] = '1';

	for (int i = 0; i < vectorSIZE; i++)
	{
		return cordMyF[i];
	}

	//return cordMyF;
}

int SetAllShipsCordinates(
	char onedeck1[2], char onedeck2[2], char onedeck3[2], char onedeck4[2],
	char twodeck1[4], char twodeck2[4], char twodeck3[4],
	char threedeck1[6], char threedeck2[6],
	char fourdeck1[8],
	vector<char>& cordMyF)
{
	// If it not default check all
	if (onedeck1[0], onedeck1[1], onedeck2[0], onedeck2[1], onedeck3[0], onedeck3[1], onedeck4[0], onedeck4[1] != '0')
	{
		int onedeck1XY = CordinatesToXY(onedeck1[0], onedeck1[1]);		//[xy]	(4)
		int onedeck2XY = CordinatesToXY(onedeck2[0], onedeck2[1]);
		int onedeck3XY = CordinatesToXY(onedeck3[0], onedeck3[1]);
		int onedeck4XY = CordinatesToXY(onedeck4[0], onedeck4[1]);

		cordMyF[onedeck1XY] = '1';
		cordMyF[onedeck2XY] = '1';
		cordMyF[onedeck3XY] = '1';
		cordMyF[onedeck4XY] = '1';
	}

	if (twodeck1[0], twodeck1[1], twodeck1[2], twodeck1[3], twodeck2[0], twodeck2[1], twodeck2[2], twodeck2[3], twodeck3[0], twodeck3[1], twodeck3[2], twodeck3[3] != '0')
	{
		int twodeck1XY1 = CordinatesToXY(twodeck1[0], twodeck1[1]);		// 1[xy], 2[xy]  (3)
		int twodeck1XY2 = CordinatesToXY(twodeck1[2], twodeck1[3]);
		int twodeck2XY1 = CordinatesToXY(twodeck2[0], twodeck2[1]);
		int twodeck2XY2 = CordinatesToXY(twodeck2[2], twodeck2[3]);
		int twodeck3XY1 = CordinatesToXY(twodeck3[0], twodeck3[1]);
		int twodeck3XY2 = CordinatesToXY(twodeck3[2], twodeck3[3]);

		cordMyF[twodeck1XY1] = '2';
		cordMyF[twodeck1XY2] = '2';
		cordMyF[twodeck2XY1] = '2';
		cordMyF[twodeck2XY2] = '2';
		cordMyF[twodeck3XY1] = '2';
		cordMyF[twodeck3XY2] = '2';
	}

	if (threedeck1[0], threedeck1[1], threedeck1[2], threedeck1[3], threedeck1[4], threedeck1[5], threedeck2[0], threedeck2[1], threedeck2[2], threedeck2[3], threedeck2[4], threedeck2[5] != '0')
	{
		int threedeck1XY1 = CordinatesToXY(threedeck1[0], threedeck1[1]);	// 1[xy], 2[xy], 3[xy] (2)
		int threedeck1XY2 = CordinatesToXY(threedeck1[2], threedeck1[3]);
		int threedeck1XY3 = CordinatesToXY(threedeck1[4], threedeck1[5]);
		int threedeck2XY1 = CordinatesToXY(threedeck2[0], threedeck2[1]);
		int threedeck2XY2 = CordinatesToXY(threedeck2[2], threedeck2[3]);
		int threedeck2XY3 = CordinatesToXY(threedeck2[4], threedeck2[5]);

		cordMyF[threedeck1XY1] = '3';
		cordMyF[threedeck1XY2] = '3';
		cordMyF[threedeck1XY3] = '3';
		cordMyF[threedeck2XY1] = '3';
		cordMyF[threedeck2XY2] = '3';
		cordMyF[threedeck2XY3] = '3';
	}

	if (fourdeck1[0], fourdeck1[1], fourdeck1[2], fourdeck1[3], fourdeck1[4], fourdeck1[5], fourdeck1[6], fourdeck1[7] != '0')
	{
		int fourdeck1XY1 = CordinatesToXY(fourdeck1[0], fourdeck1[1]);		// 1[xy], 2[xy], 3[xy], 4[xy] (1)
		int fourdeck1XY2 = CordinatesToXY(fourdeck1[2], fourdeck1[3]);
		int fourdeck1XY3 = CordinatesToXY(fourdeck1[4], fourdeck1[5]);
		int fourdeck1XY4 = CordinatesToXY(fourdeck1[6], fourdeck1[7]);

		cordMyF[fourdeck1XY1] = '4';
		cordMyF[fourdeck1XY2] = '4';
		cordMyF[fourdeck1XY3] = '4';
		cordMyF[fourdeck1XY4] = '4';
	}


	for (int i = 0; i < vectorSIZE; i++)
	{
		return cordMyF[i];
	}
}

//----------------------------------------------------------

char letters[]{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

//!================================================================================================================================================

int main()
{
	SetConsoleTitle(L"Client");

	const char ESC = 27;
	const char UP = 72;
	const char DOWN = 80;
	const char ENTER = 13;

	// Super-menu


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

	vector<char> cordMy(vectorSIZE);
	vector<char> cordEnemy(vectorSIZE);

	// Fill vector
	for (int i = 0; i < vectorSIZE; i++)
	{
		// Space
		cordMy[i] = 32;	
		cordEnemy[i] = 32;

		//cordMy[i] = '1';
		//cordEnemy[i] = '2';
	}

	//goto start;
	

	// Input
	SetConsoleTitle(L"Client - waiting for input");
	cout << "Enter your name: ";
	char name[10];
	cin >> name;
	send(Connection, name, sizeof(name), NULL);		//#1
	SetConsoleTitle(L"Client");


	// First
	char whoStartFirst[1];
	char firstUser[10];
	recvIt(firstUser);	//##1
	recvIt(whoStartFirst);	//##2
	if ((whoStartFirst[0] == '0' and name[0] == firstUser[0] and name[1] == firstUser[1]) or (whoStartFirst[0] == '1' and name[0] != firstUser[0] and name[1] != firstUser[1]))
	{
		//inputXY:
		// Send and then recive
	start:
		system("cls");
		printField(cordMy, cordEnemy, vectorSIZE, letters);
		cout << "Arranging ships:" << endl;

		CursorVisible(false);

		string menu[] = { "1-deck (4 ships)", "2-deck (3 ships)", "3-deck (2 ships)", "4-deck (1 ships)" };
		int activeMenu = 0;
		int x = 2, y = 16;		// Start position cursor for super-menu
		char ch;		// Key of button
		//char cordxy[2];

		//// Ships
		// For each ship has own cordinates
		/*
		* Formula
		* 
		* 1 ship  (1-deck) = 2 cord
		* 2 ships (1-deck) = 4 cord
		* 
		* 1 ship  (3-deck) = 6 cord	(because 1 cell = 2 cord) 2*3=6
		* 2 ships (3-deck) = 12 cord
		*/
		// Set default 0
		char onedeck1[2]{ '0', '0' };
		char onedeck2[2]{ '0', '0' };
		char onedeck3[2]{ '0', '0' };
		char onedeck4[2]{ '0', '0' };

		char twodeck1[4]{ '0', '0', '0', '0' };
		char twodeck2[4]{ '0', '0', '0', '0' };
		char twodeck3[4]{ '0', '0', '0', '0' };

		char threedeck1[6]{ '0', '0', '0', '0', '0', '0' };
		char threedeck2[6]{ '0', '0', '0', '0', '0', '0' };

		char fourdeck1[8]{ '0', '0', '0', '0', '0', '0', '0', '0'};

		// Needed for empry spaces beetwen info of arranging ships
		int spaceX = 0, spaceY = 22;

		//#Super menu
		bool AllShipsNotArranging = true;
		int AllShipsNotArrangingINT = 0;
		while (AllShipsNotArranging)
		{
			CursorVisible(false);
			x = 2, y = 17;
			Gotoxy(x, y);
			// Print menu
			for (int i = 0; i < size(menu); i++)
			{
				// Active
				if (activeMenu == i)
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					Gotoxy(x-1, y);
					cout << ">";
				}
				else
				{
					SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);
					// Clear >
					cout << "\r  ";
				}

				cout << menu[i] << "\033[0m" << endl;	// Reset color
				Gotoxy(x, ++y);		// Each step go down
			}
			
			// Listening
			ch = _getch();
			if (ch == -32) ch = _getch();

			Gotoxy(spaceX, spaceY);

			switch (ch)
			{
				case ESC:
					break;
				case UP:
					if (activeMenu > 0)
						activeMenu--;
					break;
				case DOWN:
					if (activeMenu < size(menu) - 1)
						activeMenu++;
					break;
				case ENTER:
				{

					cout << endl << endl;
					// Onedeck
					if (activeMenu == 0)
					{
						for (int i = 0; i < 4; ++i)
						{
							Gotoxy(spaceX, spaceY);
							cout << "Enter cordinates for onedeck, ";
							cout << 4 - i;
							cout << " ships left (example: A1): ";
							CursorVisible(true);

							switch (i)
							{
							case 0:
								cin >> onedeck1[0];
								cin >> onedeck1[1];
								SetAllShipsCordinates(onedeck1, onedeck2, onedeck3, onedeck4, twodeck1, twodeck2, twodeck3, threedeck1, threedeck2, fourdeck1, cordMy);
								printField(cordMy, cordEnemy, vectorSIZE, letters);
								break;
							case 1:
								cin >> onedeck2[0];
								cin >> onedeck2[1];
								SetAllShipsCordinates(onedeck1, onedeck2, onedeck3, onedeck4, twodeck1, twodeck2, twodeck3, threedeck1, threedeck2, fourdeck1, cordMy);
								printField(cordMy, cordEnemy, vectorSIZE, letters);
								break;
							case 2:
								cin >> onedeck3[0];
								cin >> onedeck3[1];
								SetAllShipsCordinates(onedeck1, onedeck2, onedeck3, onedeck4, twodeck1, twodeck2, twodeck3, threedeck1, threedeck2, fourdeck1, cordMy);
								printField(cordMy, cordEnemy, vectorSIZE, letters);
								break;
							case 3:
								cin >> onedeck4[0];
								cin >> onedeck4[1];
								SetAllShipsCordinates(onedeck1, onedeck2, onedeck3, onedeck4, twodeck1, twodeck2, twodeck3, threedeck1, threedeck2, fourdeck1, cordMy);
								printField(cordMy, cordEnemy, vectorSIZE, letters);
								break;
							default:
								break;
							}

							spaceY++;
							SetAllShipsCordinates(onedeck1, onedeck2, onedeck3, onedeck4, twodeck1, twodeck2, twodeck3, threedeck1, threedeck2, fourdeck1, cordMy);
							printField(cordMy, cordEnemy, vectorSIZE, letters);
						}

						spaceY++;
						menu[0] = "Already placed    ";
						CursorVisible(false);

						AllShipsNotArrangingINT++;
						if (AllShipsNotArrangingINT == 4)
							AllShipsNotArranging = false;
					}
					// Twodeck
					else if (activeMenu == 1)
					{
						for (int i = 0; i < 3; ++i)
						{
							Gotoxy(spaceX, spaceY);
							cout << "Enter cordinates for twodeck, ";
							cout << 3 - i;
							cout << " ships left (example: A1 B1): ";
							CursorVisible(true);

							switch (i)
							{
							case 0:
								cin >> twodeck1[0];
								cin >> twodeck1[1];
								cin >> twodeck1[2];
								cin >> twodeck1[3];
								break;
							case 1:
								cin >> twodeck2[0];
								cin >> twodeck2[1];
								cin >> twodeck2[2];
								cin >> twodeck2[3];
								break;
							case 2:
								cin >> twodeck3[0];
								cin >> twodeck3[1];
								cin >> twodeck3[2];
								cin >> twodeck3[3];
								break;
							default:
								break;
							}

							spaceY++;
							SetAllShipsCordinates(onedeck1, onedeck2, onedeck3, onedeck4, twodeck1, twodeck2, twodeck3, threedeck1, threedeck2, fourdeck1, cordMy);
							printField(cordMy, cordEnemy, vectorSIZE, letters);
						}

						spaceY++;
						menu[1] = "Already placed    ";
						CursorVisible(false);

						AllShipsNotArrangingINT++;
						if (AllShipsNotArrangingINT == 4)
							AllShipsNotArranging = false;
					}
					// Threedeck
					else if (activeMenu == 2)
					{
						for (int i = 0; i < 2; ++i)
						{
							Gotoxy(spaceX, spaceY);
							cout << "Enter cordinates for threedeck, ";
							cout << 2 - i;
							cout << " ships left (example: C1 C2 C3): ";
							CursorVisible(true);

							switch (i)
							{
							case 0:
								cin >> threedeck1[0];
								cin >> threedeck1[1];
								cin >> threedeck1[2];
								cin >> threedeck1[3];
								cin >> threedeck1[4];
								cin >> threedeck1[5];
								break;
							case 1:
								cin >> threedeck2[0];
								cin >> threedeck2[1];
								cin >> threedeck2[2];
								cin >> threedeck2[3];
								cin >> threedeck2[4];
								cin >> threedeck2[5];
								break;
							default:
								break;
							}
							spaceY++;

							SetAllShipsCordinates(onedeck1, onedeck2, onedeck3, onedeck4, twodeck1, twodeck2, twodeck3, threedeck1, threedeck2, fourdeck1, cordMy);
							printField(cordMy, cordEnemy, vectorSIZE, letters);
						}

						menu[2] = "Already placed    ";
						CursorVisible(false);

						spaceY++;
						AllShipsNotArrangingINT++;
						if (AllShipsNotArrangingINT == 4)
							AllShipsNotArranging = false;
					}
					// Fourdeck
					else if (activeMenu == 3)
					{
						Gotoxy(spaceX, spaceY);
						cout << "Enter cordinates for fourdeck, 1 ship left (example: D2 D3 D4 D5): ";
						CursorVisible(true);

						cin >> fourdeck1[0];
						cin >> fourdeck1[1];
						cin >> fourdeck1[2];
						cin >> fourdeck1[3];
						cin >> fourdeck1[4];
						cin >> fourdeck1[5];
						cin >> fourdeck1[6];
						cin >> fourdeck1[7];

						SetAllShipsCordinates(onedeck1, onedeck2, onedeck3, onedeck4, twodeck1, twodeck2, twodeck3, threedeck1, threedeck2, fourdeck1, cordMy);
						printField(cordMy, cordEnemy, vectorSIZE, letters);

						menu[3] = "Already placed    ";
						CursorVisible(false);

						spaceY++;
						AllShipsNotArrangingINT++;
						if (AllShipsNotArrangingINT == 4)
							AllShipsNotArranging = false;
					}

					break;
				}//Enter
			}
		}

		
		start2:
		//char onedeck1[2] = { 'E', '2' };
		//SetShipsCordinates(onedeck1, cordMy);

		SetAllShipsCordinates(onedeck1, onedeck2, onedeck3, onedeck4, twodeck1, twodeck2, twodeck3, threedeck1, threedeck2, fourdeck1, cordMy);
		printField(cordMy, cordEnemy, vectorSIZE, letters);
	}
	//else if (whoStartFirst[0] == '1' and name[0] != firstUser[0] and name[1] != firstUser[1])
		//goto inputXY;
	else
	{
		cout << "Waiting..." << endl;
	}
	//printField(cordMy, cordEnemy, vectorSIZE, letters);

	cout << endl << endl; system("pause"); return 0;
}