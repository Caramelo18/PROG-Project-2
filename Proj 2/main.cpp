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

int main()
{
	srand((unsigned)time(NULL));
	
	string name1, name2;
	string fich1, fich2;
	/*
	cout << "Jogador 1 introduza o nome: ";
	getline(cin, name1);
	cout << name1 << " introduza o nome do ficheiro a utilizar: ";
	cin >> fich1;
	Player::Player(name1, fich1);
	cin.ignore(1000, '\n');

	cout << "Jogador 2 introduza o nome: ";
	getline(cin, name2);
	cout << name2 << " introduza o nome do ficheiro a utilizar: ";
	cin >> fich2;
	Player::Player(name2, fich2);
	cin.ignore(1000, '\n');
	*/
	Board b("p2.txt");
	
	b.show();
	cout << endl;
	b.putShips();
	b.show();

	b.display();

	b.moveShips();

	b.display();

	return 0;
}