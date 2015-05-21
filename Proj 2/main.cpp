#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <sstream>
#include <stdlib.h>
//#include "BOMB.h"
#include "BOARD.h"
#include "SHIP.h"
#include "PLAYER.h"

using namespace std;

void clrscr(void)
{
	COORD coordScreen = { 0, 0 }; // upper left corner
	DWORD cCharsWritten;
	DWORD dwConSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hCon, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, coordScreen);
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main()
{
	srand((unsigned)time(NULL));
	
	string name1, name2;
	string fich1, fich2;
	int j = 1;
	
	/*
	cout << "Jogador 1 introduza o nome: ";
	getline(cin, name1);
	cout << name1 << " introduza o nome do ficheiro a utilizar: ";
	cin >> fich1;
	Player p1(name1, fich1);
	cin.ignore(1000, '\n');
	
	cout << "Jogador 2 introduza o nome: ";
	getline(cin, name2);
	cout << name2 << " introduza o nome do ficheiro a utilizar: ";
	cin >> fich2;
	Player p2(name2, fich2);
	cin.ignore(1000, '\n');
	*/
	Player p1("Jorge", "p2.txt");
	Player p2("Isidoro", "p1.txt");
	
	p1.getBoard().putShips();
	p2.getBoard().putShips();
	
	while (!p1.getBoard().areDestroyed() || !p2.getBoard().areDestroyed())
	{
		if (p1.getBoard().areDestroyed())
		{
			cout << name2 << "is the winner. Congratulations!" << endl;
			break;
		}
		else if (p1.getBoard().areDestroyed())
		{
			cout << name1 << "is the winner. Congratulations!" << endl;
			break;
		}

		if (j % 2 == 0)
		{
			// p1 a atacar
			cout << name1 << " it's your turn. \n";
			p2.showBoard();
			Bomb atck = p1.getBomb();
			//p2.getBoard().moveShips();
			p2.attackBoard(atck);
			cout << "\n\n";
			p2.showBoard();
			
		}
		else if (j % 2 != 0)
		{
			// p2 a atacar
			cout << name2 << " it's your turn. \n";
			p1.showBoard();
			Bomb atck = p2.getBomb();
			//p1.getBoard().moveShips();
			p1.attackBoard(atck);
			cout << "\n\n";
			p1.showBoard();
		}
		j++;

	}
		
	return 0;
}